#include "usermgr.h"
UserMgr::~UserMgr()
{
}
void UserMgr::SetName(QString name)
{
    _name = name;
}
void UserMgr::SetUid(int uid)
{
    _uid = uid;
}
void UserMgr::SetToken(QString token)
{
    _token = token;
}

void UserMgr::SetPort(QString port)
{
    _port = port;
}
UserMgr::UserMgr()
{
}

int UserMgr::GetUid()
{
    //return _user_info->_uid;
    return _uid;
}

QString UserMgr::GetName()
{
    //return _user_info->_name;
    return _name;
}

std::vector<std::shared_ptr<ApplyInfo>> UserMgr::GetApplyList() {
    return _apply_list;
}
