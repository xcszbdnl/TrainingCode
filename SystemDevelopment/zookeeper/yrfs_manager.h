// Copyright 2010 Yunrang Inc. All Rights Reserved.
// Author: jianma@yunrang.com (Ma Jian)

#ifndef UTIL_YRFS_YRFS_MANAGER_H_
#define UTIL_YRFS_YRFS_MANAGER_H_

#include <sys/ioctl.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include "base/flags.h"
#include "base/mutex.h"
#include "base/time.h"
#include "base/string_util.h"
#include "base/callback.h"
#include "base/shared_ptr.h"
#include "base/scoped_ptr.h"
#include "third_party/zookeeper/zookeeper.h"
#include "third_party/boost/boost/shared_ptr.hpp"

#include "util/yrfs/yrfs_manager_base.h"

namespace util {
class YRFSManagerBase;

struct YRFSHelpObject {
  scoped_ptr<YRFSManagerBase> manager;
  mutable base::Mutex mu;
};

class YRFSManager {
  public:
    static std::string NameSpace() { return "/YRFS"; }
    static std::string GetDefaultFullPath(
        const std::string& path);
    static std::string GetFullPathGlobal(
        const std::string& name_space,
        const std::string& datacenter,
        const std::string& path);

    static void RunAllCallbacks(
        boost::shared_ptr<YRFSHelpObject> manager_helper);
    static void Callback(
        const std::string& path,
        boost::shared_ptr<YRFSHelpObject> manager_helper);

    YRFSManager();

    YRFSManager(
        const std::string& yrfs_server,
        const std::string& datacenter);
    YRFSManager(
        const std::string& yrfs_server,
        const std::string& datacenter,
        const std::string& yrfs_userid);
    virtual ~YRFSManager();
    bool List(
        const std::string& path,
        std::vector<std::pair<std::string, std::string> >* results);
    bool Delete(
        const std::string& path,
        bool recursive);

    std::string GetData(const std::string& path,
        const base::shared_ptr<base::Closure>& closure =
        base::shared_ptr<base::Closure>(NULL));

    bool GetData(
        const std::string& path,
        std::string* result,
        const base::shared_ptr<base::Closure>& closure =
        base::shared_ptr<base::Closure>(NULL));

    bool SetData(const std::string& path, const std::string& value);
    bool Exists(const std::string& path, bool* result);
    bool Exists(const std::string& path);
    bool CreatePath(
        const std::string& path,
        const std::string& value,
        bool auto_delete = true,
        bool sequence = true);
    bool CreateSequencePath(
        const std::string& path,
        const std::string& value,
        bool auto_delete,
        std::string *real_path);
    void RegisterCallBack(
        const std::string& path,
        const base::shared_ptr<base::Closure>& closure);
    bool GetChildren(
        const std::string& path,
        std::vector<std::string>* children,
        bool watch);
    const std::string& Datacenter() {
        return datacenter_;
    }
    void Reconnect();
    void RecoverAutoDeletedPathValue();
    void OnZookeeperClosed();
    bool SetAcl(
        const std::string& path,
        AclType acl_type);
    std::string GetFullPath(
        const std::string& path);

  private:
    void Init(
        const std::string& yrfs_server,
        const std::string& datacenter,
        const std::string& yrfs_userid);
    void Init();

    std::string datacenter_;
    boost::shared_ptr<YRFSHelpObject> manager_helper_;
};

}  // namespace util

#endif  // UTIL_YRFS_YRFS_MANAGER_H_
