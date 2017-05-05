#ifndef METANFS4_COMMON_H
#define METANFS4_COMMON_H
// =============================================================================
// MetaNFS4 - user/id mapper for NFS4 mounts with the krb5 security type 
// -----------------------------------------------------------------------------
//    Copyright (C) 2016 Petr Kulhanek, kulhanek@chemi.muni.cz
//
//     This program is free software; you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation; either version 2 of the License, or
//     (at your option) any later version.
//
//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
//
//     You should have received a copy of the GNU General Public License along
//     with this program; if not, write to the Free Software Foundation, Inc.,
//     51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
// =============================================================================

/* -------------------------------------------------------------------------- */

#define SERVERPATH  "/var/run/metanfs4"
#define SERVERNAME  SERVERPATH "/metanfs4d.sock"

/* -------------------------------------------------------------------------- */
/* see man useradd */
#define MAX_NAME          32

/* correspond to char sun_path[108] in sys/un.h */
#define UNIX_PATH_MAX    108

/* max buffer for all data */
#define MAX_BUFFER       4096

/* max number of records */
#define MAX_RECORDS      4096

/* -------------------------------------------------------------------------- */
/* messages */
#define MSG_UNAUTHORIZED            0

#define MSG_IDMAP_REG_NAME          1           // registr name if not local, remove local REALM if present
#define MSG_IDMAP_REG_GROUP         2           // registr group if not local, remove local REALM if present
#define MSG_IDMAP_TO_LOCAL_DOMAIN   3           // add local REALM if necessary

#define MSG_NAME_TO_ID              4
#define MSG_ID_TO_NAME              5
#define MSG_GROUP_TO_ID             6
#define MSG_ID_TO_GROUP             7

#define MSG_ENUM_NAME               8
#define MSG_ENUM_GROUP              9
#define MSG_GROUP_MEMBER            10

#define MSG_IDMAP_PRINC_TO_ID       11

/* message structure */
struct SNFS4Message {
    int     Type;
    int     ID;
    char    Name[MAX_NAME+1];
};

/* common methods ----------------------------------------------------------- */
/* idmap */
int idmap_get_uid(const char* name);
int idmap_get_gid(const char* name);
int idmap_to_local_domain(const char* name,char* lname,int len);
int idmap_get_princ_uid(const char* name);

/* nsswitch */
int get_uid(const char* name);
int get_gid(const char* name);
int get_name(int id,char* name,int bufflen);
int get_group(int id,char* name,int bufflen);
int get_group_member(const char* gname,int id,char* name,int bufflen);

/* info services */
char* enumerate_name(int id);
char* enumerate_group(int id);

/* -------------------------------------------------------------------------- */
#endif
