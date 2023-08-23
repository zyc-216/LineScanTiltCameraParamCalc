#pragma once
#ifndef _CREADWRITESQLITEDB_H_
#define _CREADWRITESQLITEDB_H_
#include "sqlite3.h"
#include <string>
#include <map>
#include <vector>
#include <list>
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0502
#endif // !_WIN32_WINNT

enum class TYPE
{//Ŀǰ֧�ֵ���������
	INT,
	INT64, //long long
	INTEGER, //long long
	DOUBLE,
	TEXT, //string
	BLOB, //string
	NULL_
};
typedef struct
{
	//keyΪstring������
	//buffer, sqlite һ��5������, NULL, INTEGER(1~8byte,long longΪ8���ֽڵ�����),REAL��double 8byte��,text�ı��ַ���, BLOB�ڴ��
	std::map<std::string, std::vector<long long>*>	 m_mapINTEGER;
	std::map<std::string, std::vector<double>*>		 m_mapREAL;
	std::map<std::string, std::vector<std::string>*> m_mapTEXT;
	std::map<std::string, std::vector<std::string>*> m_mapBLOB;
} TableMapData;
class CReadWriteSqliteDB
{
	typedef struct
	{
		std::vector<std::string> vecColNames;
		std::vector<TYPE>         vecColTypes;
	} ColNamesAndTypes;

public:
	CReadWriteSqliteDB();
	~CReadWriteSqliteDB();
	friend class scheimCamera;
	bool 	OpenDB(const char* strFileName); //�����ݿ⣬�������ڣ��򴴽�
	//bool	OpenDB(sqlite3* pDb);
	bool	CloseDB();
	bool	CreateTable(const char* strSql, const char* strTableName);
	bool	Read(const char* strTableName, int indexStart, int iCounts);  //sqlite�������ӵ�0�п�ʼ
	bool	Append(const char* strTableName, int iCounts,std::initializer_list<void*>);	//�б��ʼ�������ձ��col����˳�� void*->vector<>*
	//bool	Delete(const char* strTableName, std::initializer_list<void*>); //�б��ʼ���е�ָ��ָ��ָ��ɾ���еĸ��ֶ�ֵ
	TableMapData& GetTableData(const char* strTableName);

private:
	bool	ReadStmt(sqlite3_stmt* pStmt, const char* strTableName);
	int		GetDataCounts(const char* strTableName); //��ȡ���е���������:1.exec+�ص� 2.get_table 3.stmt+step
	bool	GetTableNames();
	bool	GetColNamesTypes(const char* strTableName);
	void	ClearTableNames();
	void	ClearColNamesTypes();
	bool	ClearTableData(const char* strTableName);
	std::string GbkToUtf8(const std::string& str);

private:
	sqlite3*											m_pSqlitedb;
	std::list<std::string>								m_listStrTableNames;
	std::map<std::string, TableMapData>					m_tableMapData;  //key:����, value:����colName�������ݵ�map
	std::map<std::string, ColNamesAndTypes>	m_tableMapColNamesTypes; //key������, value:���δ��colName��Type��vector
};
#endif // !_CREADWRITESQLITEDB_H_
