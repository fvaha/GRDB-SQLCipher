#ifndef CSQLITE_SHIM_H
#define CSQLITE_SHIM_H

#include <sqlite3.h>

// SQLCipher encryption APIs (not in standard sqlite3.h)
#ifdef SQLITE_HAS_CODEC
int sqlite3_key(sqlite3 *db, const void *pKey, int nKey);
int sqlite3_key_v2(sqlite3 *db, const char *zDbName, const void *pKey, int nKey);
int sqlite3_rekey(sqlite3 *db, const void *pKey, int nKey);
int sqlite3_rekey_v2(sqlite3 *db, const char *zDbName, const void *pKey, int nKey);
void sqlite3_activate_see(const char *zPassPhrase);
#endif

typedef void(*_errorLogCallback)(void *pArg, int iErrCode, const char *zMsg);

static inline void _registerErrorLogCallback(_errorLogCallback callback) {
    sqlite3_config(SQLITE_CONFIG_LOG, callback, 0);
}

#if SQLITE_VERSION_NUMBER >= 3029000
static inline void _disableDoubleQuotedStringLiterals(sqlite3 *db) {
    sqlite3_db_config(db, SQLITE_DBCONFIG_DQS_DDL, 0, (void *)0);
    sqlite3_db_config(db, SQLITE_DBCONFIG_DQS_DML, 0, (void *)0);
}

static inline void _enableDoubleQuotedStringLiterals(sqlite3 *db) {
    sqlite3_db_config(db, SQLITE_DBCONFIG_DQS_DDL, 1, (void *)0);
    sqlite3_db_config(db, SQLITE_DBCONFIG_DQS_DML, 1, (void *)0);
}
#else
static inline void _disableDoubleQuotedStringLiterals(sqlite3 *db) { }
static inline void _enableDoubleQuotedStringLiterals(sqlite3 *db) { }
#endif

#ifdef GRDB_SQLITE_ENABLE_PREUPDATE_HOOK
SQLITE_API void *sqlite3_preupdate_hook(sqlite3 *db, void(*xPreUpdate)(void *pCtx, sqlite3 *db, int op, char const *zDb, char const *zName, sqlite3_int64 iKey1, sqlite3_int64 iKey2), void*);
SQLITE_API int sqlite3_preupdate_old(sqlite3 *, int, sqlite3_value **);
SQLITE_API int sqlite3_preupdate_count(sqlite3 *);
SQLITE_API int sqlite3_preupdate_depth(sqlite3 *);
SQLITE_API int sqlite3_preupdate_new(sqlite3 *, int, sqlite3_value **);
#endif

#endif /* CSQLITE_SHIM_H */
