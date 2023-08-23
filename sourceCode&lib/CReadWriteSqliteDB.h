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
{//目前支持的数据类型
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
	//key为string，列名
	//buffer, sqlite 一共5种类型, NULL, INTEGER(1~8byte,long long为8个字节的整数),REAL（double 8byte）,text文本字符串, BLOB内存块
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
	bool 	OpenDB(const char* strFileName); //打开数据库，若不存在，则创建
	//bool	OpenDB(sqlite3* pDb);
	bool	CloseDB();
	bool	CreateTable(const char* strSql, const char* strTableName);
	bool	Read(const char* strTableName, int indexStart, int iCounts);  //sqlite表索引从第0行开始
	bool	Append(const char* strTableName, int iCounts,std::initializer_list<void*>);	//列表初始化，按照表的col创建顺序 void*->vector<>*
	//bool	Delete(const char* strTableName, std::initializer_list<void*>); //列表初始化中的指针指向指定删除行的各字段值
	TableMapData& GetTableData(const char* strTableName);

private:
	bool	ReadStmt(sqlite3_stmt* pStmt, const char* strTableName);
	int		GetDataCounts(const char* strTableName); //获取表中的数据总数:1.exec+回调 2.get_table 3.stmt+step
	bool	GetTableNames();
	bool	GetColNamesTypes(const char* strTableName);
	void	ClearTableNames();
	void	ClearColNamesTypes();
	bool	ClearTableData(const char* strTableName);
	std::string GbkToUtf8(const std::string& str);

private:
	sqlite3*											m_pSqlitedb;
	std::list<std::string>								m_listStrTableNames;
	std::map<std::string, TableMapData>					m_tableMapData;  //key:表名, value:根据colName查找数据的map
	std::map<std::string, ColNamesAndTypes>	m_tableMapColNamesTypes; //key：表名, value:依次存放colName和Type的vector
};
#endif // !_CREADWRITESQLITEDB_H_
