#include "CReadWriteSqliteDB.h"
//#include "macrodef.h"
#include <Windows.h>
#include <iostream>
//#include <qdebug.h>
CReadWriteSqliteDB::CReadWriteSqliteDB()
{
	m_pSqlitedb = nullptr;

}

CReadWriteSqliteDB::~CReadWriteSqliteDB()
{
	if (m_pSqlitedb)
		CloseDB();
}

bool CReadWriteSqliteDB::OpenDB(const char* strFileName)
{
	bool bRet = false;
	if (SQLITE_OK != sqlite3_open_v2(GbkToUtf8(strFileName).data(), &m_pSqlitedb, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL))
		return bRet;
	GetTableNames();
	for (std::list<std::string>::iterator iter = m_listStrTableNames.begin(); iter != m_listStrTableNames.end(); ++iter)
	{
		GetColNamesTypes(iter->c_str());
	}
	bRet = true;
	return bRet;
}

//bool CReadWriteSqliteDB::OpenDB(sqlite3* pDb)
//{
//	bool bRet = false;
//	if (nullptr == pDb)
//		return bRet;
//	bRet = true;
//	return bRet;
//}

bool CReadWriteSqliteDB::CloseDB()
{
	bool bRet = false;
	if (nullptr == m_pSqlitedb)
		return bRet;
	sqlite3_close_v2(m_pSqlitedb);
	m_pSqlitedb = nullptr;
	do 
	{
		for (std::map<std::string, TableMapData>::iterator iterTable = m_tableMapData.begin(); iterTable != m_tableMapData.end(); ++iterTable)
		{
			if(!ClearTableData(iterTable->first.c_str())) 
				return bRet;
		}
		ClearTableNames();
		ClearColNamesTypes();
		if (m_tableMapData.size() != 0)
			return bRet;
		bRet = true;
	} while (0);

	return bRet;
}

bool CReadWriteSqliteDB::CreateTable(const char* strSql, const char* strTableName)
{
	//表不存在，则创建成功，返回true
	//表已存在，或者，创建失败，则返回false
	bool bRet = false;
	sqlite3_exec(m_pSqlitedb, strSql, NULL, NULL, 0);
	for (auto& i : m_listStrTableNames)
	{
		if (i == strTableName)
			return bRet;
	}
	m_listStrTableNames.push_back(strTableName);
	GetColNamesTypes(strTableName);
	bRet = true;
	return bRet;
}

bool CReadWriteSqliteDB::Read(const char* strTableName, int indexStart, int iCounts)
{
	bool bRet = false;
	char strSql[1024] = { 0 };
	sqlite3_stmt* pStmt = nullptr;
	int iTableDataCount= GetDataCounts(strTableName);
	iCounts = iCounts > iTableDataCount ? iTableDataCount : iCounts;
	sprintf_s(strSql, 1024, "select * from %s limit %d, %d", strTableName, indexStart, iCounts);
	std::cout << strSql << std::endl;
	if (SQLITE_OK != sqlite3_prepare_v2(m_pSqlitedb, strSql, -1, &pStmt, 0))
		return bRet;
	//一行一行读取
	bool isFirstForRange = true;
	while (SQLITE_ROW == sqlite3_step(pStmt))
	{
		if (!ReadStmt(pStmt, strTableName))
			return bRet;

	}
	if (SQLITE_OK != sqlite3_finalize(pStmt))
		return bRet;
	bRet = true;
	return bRet;
}

bool CReadWriteSqliteDB::Append(const char* strTableName, int iCounts, std::initializer_list<void*> init_list)
{
	bool bRet = false;
	//init_list赋值给mapData
	std::vector<void*> vecData = init_list;
	sqlite3_stmt* pStmt = nullptr;
	//sql语句
	std::string strSql;
	std::string sqlLeft = "INSERT INTO " + std::string(strTableName) + "(";
	std::string sqlRight = " VALUES(";
	for (int i = 0; i <m_tableMapColNamesTypes[strTableName].vecColNames.size(); ++i)
	{
		sqlLeft += m_tableMapColNamesTypes[strTableName].vecColNames.at(i);
		sqlRight += "?";
		if (i < m_tableMapColNamesTypes[strTableName].vecColNames.size() - 1)
		{
			sqlLeft += ",";
			sqlRight += ",";
		}
		else
		{
			sqlRight += ")";
			sqlLeft += ")";
		}
	}
	strSql = sqlLeft + sqlRight;
	if (SQLITE_OK != sqlite3_prepare_v2(m_pSqlitedb, strSql.c_str(), -1/* strSql.size()*/, &pStmt, 0))
		return bRet;
	//循环绑定，写入数据库
	for (int i = 0; i < iCounts; ++i)
	{
		for (int j = 0; j < m_tableMapColNamesTypes[strTableName].vecColNames.size(); ++j)
		{
			std::string strColName = m_tableMapColNamesTypes[strTableName].vecColNames.at(j);
			TYPE iColType = m_tableMapColNamesTypes[strTableName].vecColTypes.at(j);
			if (TYPE::INT == iColType)
				sqlite3_bind_int(pStmt, j + 1, ((std::vector<int>*)vecData[j])->at(i));
			if (TYPE::INT64 == iColType|| TYPE::INTEGER==iColType)
				sqlite3_bind_int64(pStmt, j + 1, ((std::vector<long long>*)vecData[j])->at(i));
			if (TYPE::DOUBLE == iColType)
				sqlite3_bind_double(pStmt, j + 1, ((std::vector<double>*)vecData[j])->at(i));
			if (TYPE::BLOB == iColType)
				sqlite3_bind_blob(pStmt, j + 1, ((std::vector<std::string>*)vecData[j])->at(i).c_str(),
					((std::vector<std::string>*)vecData[j])->at(i).size(), nullptr);
			if (TYPE::TEXT == iColType)
				sqlite3_bind_text(pStmt, j + 1, ((std::vector<std::string>*)vecData[j])->at(i).c_str(),
					((std::vector<std::string>*)vecData[j])->at(i).size(), nullptr);
			if (TYPE::NULL_ == iColType)
				sqlite3_bind_null(pStmt, j + 1);
		}
		sqlite3_step(pStmt);
		sqlite3_reset(pStmt);
	}
	sqlite3_finalize(pStmt);
	pStmt = nullptr;
	bRet = true;
	return bRet;
}

//bool CReadWriteSqliteDB::Delete(const char* strTableName,std::initializer_list<void*>)
//{
//	for()
//	bool bRet = false;
//	char strSqlDelete[1024] = { 0 };
//	char* pErrMsg = 0;
//	//WHERE id = '%d'
//	sprintf_s(strSqlDelete, 1024, "DELETE FROM %s WHERE width = 2560 ", strTableName);
//	qDebug() <<QString( strSqlDelete);
//	if (SQLITE_OK != sqlite3_exec(m_pSqlitedb, strSqlDelete, NULL, NULL, &pErrMsg))
//	{
//		qDebug() << "操作发生失败，失败原因:" << pErrMsg << endl;;
//		sqlite3_free(pErrMsg);
//		return bRet;
//	}bRet = true;
//	return bRet;
//}

TableMapData& CReadWriteSqliteDB::GetTableData(const char* strTableName)
{
	return m_tableMapData[strTableName];
}



bool CReadWriteSqliteDB::ReadStmt(sqlite3_stmt* pStmt, const char* strTableName)
{
	bool bRet = false;
	if (nullptr == pStmt)
		return bRet;
	TableMapData& tableColMap = m_tableMapData[strTableName];
	int iColType = 0;
	std::string strColName;
	int iColCount = sqlite3_column_count(pStmt);
	for (int i = 0; i < iColCount; i++)
	{
		iColType = sqlite3_column_type(pStmt, i);
		strColName = sqlite3_column_name(pStmt, i);
		if (SQLITE_INTEGER == iColType)
		{
			if (tableColMap.m_mapINTEGER.find(strColName) == tableColMap.m_mapINTEGER.end())
			{
				tableColMap.m_mapINTEGER[strColName] = new std::vector<long long>{};
				tableColMap.m_mapINTEGER[strColName]->push_back(sqlite3_column_int64(pStmt, i));
			}
			else
			{
				tableColMap.m_mapINTEGER[strColName]->push_back(sqlite3_column_int64(pStmt, i));
			}
		}
		if (SQLITE_BLOB == iColType)
		{
			if (tableColMap.m_mapBLOB.find(strColName) == tableColMap.m_mapBLOB.end())
			{
				tableColMap.m_mapBLOB[strColName] = new std::vector<std::string>{};
				tableColMap.m_mapBLOB[strColName]->push_back(std::string((const char*)sqlite3_column_blob(pStmt, i)));
			}
			else
			{
				tableColMap.m_mapBLOB[strColName]->push_back(std::string((const char*)sqlite3_column_blob(pStmt, i)));
			}
		}

		if (SQLITE_TEXT == iColType)
		{
			if (tableColMap.m_mapTEXT.find(strColName) == tableColMap.m_mapTEXT.end())
			{
				tableColMap.m_mapTEXT[strColName] = new std::vector<std::string>{};
				tableColMap.m_mapTEXT[strColName]->push_back(std::string((const char*)sqlite3_column_text(pStmt, i)));
			}
			else
			{
				tableColMap.m_mapTEXT[strColName]->push_back(std::string((const char*)sqlite3_column_text(pStmt, i)));
			}
		}
		if (SQLITE_FLOAT == iColType)
		{
			if (tableColMap.m_mapREAL.find(strColName) == tableColMap.m_mapREAL.end())
			{
				tableColMap.m_mapREAL[strColName] = new std::vector<double>{};
				tableColMap.m_mapREAL[strColName]->push_back(sqlite3_column_double(pStmt, i));
			}
			else
			{
				tableColMap.m_mapREAL[strColName]->push_back(sqlite3_column_double(pStmt, i));
			}
		}
	}
	bRet = true;
	return bRet;
}

int CReadWriteSqliteDB::GetDataCounts(const char* strTableName)
{
	char strSql[1024] = { 0 };
	sprintf_s(strSql, 1024, "SELECT count(*) FROM %s", strTableName);
	char** dbResult;
	int row, col;
	if (SQLITE_OK != sqlite3_get_table(m_pSqlitedb, strSql, &dbResult, &row, &col, NULL))
		return -1;
	int iRet =std::atoi( dbResult[col + 0]);
	sqlite3_free_table(dbResult);
	return iRet;
}

bool CReadWriteSqliteDB::GetTableNames()
{
	bool bRet = false;
	if (nullptr == m_pSqlitedb)
		return bRet;
	char** dbResult;
	int row, col;
	if(SQLITE_OK != sqlite3_get_table(m_pSqlitedb, "SELECT name FROM sqlite_master WHERE type='table' ORDER BY name", &dbResult, &row, &col, NULL))
		return bRet;
	for (int i = 0; i < row; ++i)
	{
		std::cout << dbResult[col + i * col] << std::endl;
		m_listStrTableNames.push_back(dbResult[col + i * col]);
	}
	sqlite3_free_table(dbResult);
	bRet = true;
	return bRet;
}

bool CReadWriteSqliteDB::GetColNamesTypes(const char* strTableName)
{
	bool bRet = false;
	if (nullptr == m_pSqlitedb)
		return bRet;
	char strSql[1024] = { 0 };
	sprintf_s(strSql, 1024, "PRAGMA table_info (%s)", strTableName);
	char** dbResult;
	int row, col;
	if(SQLITE_OK!= sqlite3_get_table(m_pSqlitedb, strSql, &dbResult, &row, &col, NULL))
		return bRet;
	std::string strType;
	for (int i = 0; i < row; ++i)
	{
		m_tableMapColNamesTypes[strTableName].vecColNames.push_back(dbResult[col+1+i*col]);
		strType= std::string(dbResult[col + 2 + i * col]);
		if ("INTEGER" == strType|| "integer" == strType)
		{
			m_tableMapColNamesTypes[strTableName].vecColTypes.push_back(TYPE::INTEGER);
		}
		else if ("INT" == strType|| "int" == strType)
		{
			m_tableMapColNamesTypes[strTableName].vecColTypes.push_back(TYPE::INT);
		}
		else if ("INT64" == strType|| "int64" == strType)
		{
			m_tableMapColNamesTypes[strTableName].vecColTypes.push_back(TYPE::INT64);
		}
		else if ("TEXT" == strType|| "text" == strType)
		{
			m_tableMapColNamesTypes[strTableName].vecColTypes.push_back(TYPE::TEXT);
		}
		else if ("BLOB" == strType|| "blob" == strType)
		{
			m_tableMapColNamesTypes[strTableName].vecColTypes.push_back(TYPE::BLOB);
		}
		else if ("DOUBLE" == strType||"double" == strType)
		{
			m_tableMapColNamesTypes[strTableName].vecColTypes.push_back(TYPE::DOUBLE);
		}
		else
		{
			m_tableMapColNamesTypes[strTableName].vecColTypes.push_back(TYPE::NULL_);
		}

	}
	sqlite3_free_table(dbResult);
	bRet = true;
	return bRet;
}



void CReadWriteSqliteDB::ClearTableNames()
{
	m_listStrTableNames.clear();
}

void CReadWriteSqliteDB::ClearColNamesTypes()
{
	m_tableMapColNamesTypes.clear();
}



bool CReadWriteSqliteDB::ClearTableData(const char* strTableName)
{
	bool bRet = false;
	if (m_tableMapData.end() == m_tableMapData.find(strTableName))
		return bRet;
	for (std::map<std::string, std::vector<long long>*>::iterator iter = m_tableMapData[strTableName].m_mapINTEGER.begin();
		iter != m_tableMapData[strTableName].m_mapINTEGER.end(); iter++)
	{
		if (iter->second)
			delete iter->second;
		iter->second = nullptr;
	}
	for (std::map<std::string, std::vector<double>*>::iterator iter = m_tableMapData[strTableName].m_mapREAL.begin();
		iter != m_tableMapData[strTableName].m_mapREAL.end(); iter++)
	{
		if (iter->second)
			delete iter->second;
		iter->second = nullptr;
	}
	for (std::map<std::string, std::vector<std::string>*>::iterator iter = m_tableMapData[strTableName].m_mapBLOB.begin();
		iter != m_tableMapData[strTableName].m_mapBLOB.end(); iter++)
	{
		if (iter->second)
			delete iter->second;
		iter->second = nullptr;
	}
	for (std::map<std::string, std::vector<std::string>*>::iterator iter = m_tableMapData[strTableName].m_mapTEXT.begin();
		iter != m_tableMapData[strTableName].m_mapTEXT.end(); iter++)
	{
		if (iter->second)
			delete iter->second;
		iter->second = nullptr;
	}

	for (std::map<std::string, TableMapData>::iterator iter = m_tableMapData.begin(); iter != m_tableMapData.end(); ++iter)
	{
		if (strTableName == iter->first)
		{
			m_tableMapData.erase(iter);
			break;
		}
	}
	bRet = true;
	return bRet;
}

//bool CReadWriteSqliteDB::ClearBuffer()
//{
//	bool bRet = false;
//	//
//	for (std::map<std::string, TableColMap>::iterator iterTable = m_tableMapData.begin(); iterTable != m_tableMapData.end(); ++iterTable)
//	{
//		for (std::map<std::string, std::vector<long long>*>::iterator iter = iterTable->second.m_mapINTEGER.begin();
//			iter != iterTable->second.m_mapINTEGER.end(); iter++)
//		{
//			if (iter->second)
//				delete iter->second;
//			iter->second = nullptr;
//		}
//		for (std::map<std::string, std::vector<double>*>::iterator iter = iterTable->second.m_mapREAL.begin();
//			iter != iterTable->second.m_mapREAL.end(); iter++)
//		{
//			if (iter->second)
//				delete iter->second;
//			iter->second = nullptr;
//		}
//		for (std::map<std::string, std::vector<std::string>*>::iterator iter = iterTable->second.m_mapBLOB.begin();
//			iter != iterTable->second.m_mapBLOB.end(); iter++)
//		{
//			if (iter->second)
//				delete iter->second;
//			iter->second = nullptr;
//		}
//		for (std::map<std::string, std::vector<std::string>*>::iterator iter = iterTable->second.m_mapTEXT.begin();
//			iter != iterTable->second.m_mapTEXT.end(); iter++)
//		{
//			if (iter->second)
//				delete iter->second;
//			iter->second = nullptr;
//		}
//	}
//	m_tableMapData.clear();
//	//
//	for (std::map<std::string, std::vector<std::string>*>::iterator iter = m_tableMapColNames.begin(); iter != m_tableMapColNames.end(); iter++)
//	{
//		if (iter->second)
//			delete iter->second;
//		iter->second = nullptr;
//	}
//	m_tableMapColNames.clear();
//	//
//	for (std::map<std::string, std::vector<int>*>::iterator iter = m_tableMapColTypes.begin(); iter != m_tableMapColTypes.end(); iter++)
//	{
//		if (iter->second)
//			delete iter->second;
//		iter->second = nullptr;
//	}
//	m_tableMapColTypes.clear();
//	bRet = true;
//	return bRet;
//}

//int CReadWriteSqliteDB::GetTableCount(const char* strTableName)
//{
//	char strSql[1024] = { 0 };
//	char** ppResult;
//	int iRowCount;
//	int iColCount;
//	sprintf_s(strSql, 1024, "SELECT * FROM %s", strTableName);
//	if (SQLITE_OK != sqlite3_get_table(m_pSqlitedb, strSql, &ppResult, &iRowCount, &iColCount, 0))
//	{
//		sqlite3_free_table(ppResult);
//		return -1;
//	}
//
//	return iRowCount - 1; //第一行是字段名
//}

//bool CReadWriteSqliteDB::GetMapColNames(const char* strTableName)
//{
//	bool bRet = false;
//	sqlite3_stmt* stmt = nullptr;
//	if (m_tableMapColNames.find(strTableName) == m_tableMapColNames.end())
//	{
//		m_tableMapColNames[strTableName] = new std::vector<std::string>{};
//	}
//	else
//	{
//		qDebug() << "表已经存在";
//		return bRet;
//	}
//	char sql[1024] = { 0 };
//	sprintf_s(sql, 1024, "PRAGMA table_info (%s)", strTableName);
//	char** pRes = NULL;
//	int nRow = 0, nCol = 0;
//	char* pErr = NULL;
//	if (SQLITE_OK != sqlite3_get_table(m_pSqlitedb, sql, &pRes, &nRow, &nCol, 0))
//	{
//		qDebug() << "get_table 出错";
//		sqlite3_free_table(pRes);
//		return bRet;
//	}
//	//遍历第一行
//	qDebug() << "cols:" << nRow << nCol;
//	for (int j = 0; j < nRow; j++)
//	{
//		const char* colName = pRes[1 + nCol * j];// *(pRes + 1+nCol*j);
//		//int colType= atoi(pRes[2 + nCol * j]);
//		qDebug() << pRes[0];// << colType;
//		m_tableMapColNames[strTableName]->push_back(colName);
//		//m_tableMapColTypes[strTableName]->push_back(colType);
//	}
//	sqlite3_free_table(pRes);
//	bRet = true;
//	return bRet;
//}
//
//bool CReadWriteSqliteDB::GetMapColTypes(const char* strTableName)
//{
//	bool bRet = false;
//	if (m_tableMapColTypes.find(strTableName) == m_tableMapColTypes.end())
//	{
//		m_tableMapColTypes[strTableName] = new std::vector<int>{};
//	}
//	else
//	{
//		return bRet;
//	}
//	sqlite3_stmt* pStmt = NULL;
//	char strSql[1024] = { 0 };
//	sprintf(strSql, "SELECT * FROM %s limit 0,1", strTableName);
//	if (SQLITE_OK != sqlite3_prepare(m_pSqlitedb, strSql, -1, &pStmt, 0))
//		return bRet;
//	if (pStmt)
//	{
//		while (sqlite3_step(pStmt) == SQLITE_ROW)
//		{
//			int iColCount = sqlite3_column_count(pStmt);
//			for (int i = 0; i < iColCount; i++)
//			{
//				int iType = sqlite3_column_type(pStmt, i);
//				m_tableMapColTypes[strTableName]->push_back(iType);
//				//1 SQLITE_INTEGER
//				//2 SQLITE_FLOAT
//				//3 SQLITE_TEXT
//				//4 SQLITE_BLOB
//				//5 SQLITE_NULL
//			}
//			break;
//		}
//		sqlite3_finalize(pStmt);
//		pStmt = nullptr;
//	}
//	bRet = true;
//	return bRet;
//}

std::string CReadWriteSqliteDB::GbkToUtf8(const std::string& str)
{
	// Convert the input string to a UTF-16 output buffer
	int wBufferSize = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
	wchar_t* wBuffer = new wchar_t[wBufferSize];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wBuffer, wBufferSize);

	// Convert the UTF-16 output buffer to a UTF-8 output buffer
	int u8BufferSize = WideCharToMultiByte(CP_UTF8, 0, wBuffer, -1, nullptr, 0, nullptr, nullptr);
	char* u8Buffer = new char[u8BufferSize];
	WideCharToMultiByte(CP_UTF8, 0, wBuffer, -1, u8Buffer, u8BufferSize, nullptr, nullptr);

	// Create a string from the UTF-8 output buffer
	std::string utf8String(u8Buffer);

	// Clean up
	delete[] wBuffer;
	delete[] u8Buffer;

	return utf8String;
}
