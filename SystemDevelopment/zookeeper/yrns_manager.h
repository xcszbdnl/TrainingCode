// Copyright 2010 Yunrang Inc. All Rights Reserved.
// Author: jianma@yunrang.com (Ma Jian)

#ifndef UTIL_YRNS_YRNS_MANAGER_H_
#define UTIL_YRNS_YRNS_MANAGER_H_

#include <sys/ioctl.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <utility>
#include "base/flags.h"
#include "base/time.h"
#include "base/mutex.h"
#include "base/string_util.h"
#include "base/callback.h"
#include "base/shared_ptr.h"
#include "util/yrfs/yrfs_manager.h"

namespace util {

struct YRNSReplicaInfo {
  int replica_id;
  std::string hostname;
  int port;
};

class YRNSManager : public YRFSManager {
  public:
    static const std::string SERVICE_RPC;
    static const std::string SERVICE_MONITOR;
    static const std::string SERVICE_FRONTEND;

    YRNSManager();

    YRNSManager(
        const std::string& yrns_server,
        const std::string& datacenter);
    ~YRNSManager();

    // Static methods
    static std::string NameSpace() { return "/YRNS"; }

    static std::string GetDefaultFullPath(
        const std::string& path,
        const std::string& port_name,
        int replica_id);

    static std::string GetDefaultFullPath(
        const std::string& path,
        const std::string& port_name);

    static std::string GetFullPathHelper(
        const std::string& datacenter,
        const std::string& path);

    static std::string GetFullPathHelper(
        const std::string& datacenter,
        const std::string& path,
        const std::string& port_name);

    bool Get(
        const std::string& path,
        std::string* host,
        int* port,
        const base::shared_ptr<base::Closure>& closure =
        base::shared_ptr<base::Closure>(NULL));
    bool TryGet(
        const std::string& path,
        bool* exists,
        std::string* host,
        int* port,
        const base::shared_ptr<base::Closure>& closure);

    bool GetAllReplicas(
        const std::string& path,
        const std::string& port_name,
        std::vector<std::pair<std::string, int> >* results,
        const base::shared_ptr<base::Closure>& closure =
        base::shared_ptr<base::Closure>(NULL));

    bool GetAllReplicas(
        const std::string& path,
        std::vector<std::pair<std::string, int> >* results,
        const base::shared_ptr<base::Closure>& closure =
        base::shared_ptr<base::Closure>(NULL));

    bool GetAllReplicas(
        const std::string& path,
        const std::string& port_name,
        std::vector<YRNSReplicaInfo>* results,
        const base::shared_ptr<base::Closure>& closure =
        base::shared_ptr<base::Closure>(NULL));

    bool GetAllReplicas(
        const std::string& path,
        std::vector<YRNSReplicaInfo>* results,
        const base::shared_ptr<base::Closure>& closure =
        base::shared_ptr<base::Closure>(NULL));

    // When YRNSManager is destructed, the registered path will be removed
    // automatcally
    bool Register(
        const std::string& path,
        const std::string& port_name,
        std::string hostname,
        int port,
        bool auto_delete = true,
        AclType acl_type = ACL_TYPE_NONE) {
      return Register(
          path,
          0,
          port_name,
          hostname,
          port,
          auto_delete,
          acl_type);
    }

    bool Register(
        const std::string& path,
        int replica_id,
        const std::string& port_name,
        std::string hostname,
        int port,
        bool auto_delete = true,
        AclType acl_type = ACL_TYPE_NONE);

    bool Register(
        const std::string& path,
        const std::string& port_name,
        int port,
        bool auto_delete = true,
        AclType acl_type = ACL_TYPE_NONE) {
      return Register(
          path,
          0,
          port_name,
          port,
          auto_delete,
          acl_type);
    }

    bool Register(
        const std::string& path,
        int replica_id,
        const std::string& port_name,
        int port,
        bool auto_delete = true,
        AclType acl_type = ACL_TYPE_NONE);

    std::string GetFullPath(
        const std::string& path);

    std::string GetFullPath(
        const std::string& path,
        const std::string& port_name);

    std::string GetFullPath(
        const std::string& path,
        const std::string& port_name,
        int replica_id);
    std::string Hostname();
  private:
    void Init();
    bool GetInternal(
        const std::string& full_path,
        const std::string& child_name,
        std::vector<std::pair<std::string, int> >* results,
        const base::shared_ptr<base::Closure>& closure =
        base::shared_ptr<base::Closure>(NULL));

    bool GetInternal(
        const std::string& full_path,
        const std::string& child_name,
        std::vector<YRNSReplicaInfo>* results,
        const base::shared_ptr<base::Closure>& closure =
        base::shared_ptr<base::Closure>(NULL));

    std::string hostname_;
};

}  // namespace util

#endif  // UTIL_YRNS_YRNS_MANAGER_H_
