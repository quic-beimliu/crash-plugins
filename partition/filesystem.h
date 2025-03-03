// Copyright (c) 2024-2025 Qualcomm Innovation Center, Inc. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause-Clear

#ifndef FILESYSTEM_DEFS_H_
#define FILESYSTEM_DEFS_H_

#include "plugin.h"

class Mount : public PaserPlugin{
public:
    ulong addr;
    ulong f_bsize;
    ulong f_blocks;
    ulong f_bfree;
    ulong f_bavail;
    std::string dev_name;
    std::string dir_name;
    std::string fs_type;
    ulong sb_addr;
    ulong fs_addr;
    ulong fs_info_addr;
    int mnt_flags;
    std::vector<std::shared_ptr<Mount>> childs;

    void cmd_main(void) override;
    virtual void statfs(int width);
};

class F2fs: public Mount {
public:
    F2fs();
    void statfs(int width) override;
};

class Ext4 : public Mount {
public:
    Ext4();
    void statfs(int width) override;
    long long percpu_counter_sum(ulong addr);
};

class FileSystem : public PaserPlugin {
public:
    std::vector<std::shared_ptr<Mount>> mount_list;
    std::unordered_map<size_t, std::shared_ptr<Mount>> sb_list;
    FileSystem();

    void cmd_main(void) override;
    std::shared_ptr<Mount> parser_mount(ulong mount_addr);
    void print_mount_tree(std::vector<std::shared_ptr<Mount>>& mnt_list,int level);
    void print_partition_size(void);
    void parser_mount_tree(void);
    void parser_mount_tree(ulong mount_addr,std::vector<std::shared_ptr<Mount>>& mnt_list);
    DEFINE_PLUGIN_INSTANCE(FileSystem)
};

#endif // FILESYSTEM_DEFS_H_
