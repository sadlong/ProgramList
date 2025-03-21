#ifndef USERMGR_H
#define USERMGR_H
#include <QObject>
#include <memory>
#include <singleton.h>
#include "userdata.h"
#include <vector>

class UserMgr:public QObject,public Singleton<UserMgr>,
        public std::enable_shared_from_this<UserMgr>
{
    Q_OBJECT
public:
    friend class Singleton<UserMgr>;
    ~ UserMgr();
    void SetName(QString name);
    void SetUid(int uid);
    void SetToken(QString token);
    void SetPort(QString port);
    int GetUid();
    QString GetName();
    std::vector<std::shared_ptr<ApplyInfo>> GetApplyList();
private:
    UserMgr();
    QString _name;
    QString _token;
    int _uid;
    QString _port;
    std::vector<std::shared_ptr<ApplyInfo>> _apply_list;
    //std::shared_ptr<UserInfo> _user_info;
};
#endif // USERMGR_H
