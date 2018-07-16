// File author is Ítalo Lima Marconato Matias
//
// Created on July 16 of 2018, at 18:18 BRT
// Last edited on July 16 of 2018, at 20:14 BRT

#ifndef __CHICAGO_FILE_H__
#define __CHICAGO_FILE_H__

#include <chicago/device.h>
#include <chicago/list.h>

#define FS_FLAG_DIR 0x01
#define FS_FLAG_FILE 0x02

typedef struct FsNodeStruct {
	PChar name;
	UIntPtr flags;
	UIntPtr inode;
	PDevice device;
	Boolean (*read)(struct FsNodeStruct *, UIntPtr, UIntPtr, PUInt8);
	Boolean (*write)(struct FsNodeStruct *, UIntPtr, UIntPtr, PUInt8);
	Boolean (*open)(struct FsNodeStruct *);
	Void (*close)(struct FsNodeStruct *);
	PChar (*readdir)(struct FsNodeStruct *, UIntPtr);
	struct FsNodeStruct *(*finddir)(struct FsNodeStruct *, PChar);
} FsNode, *PFsNode;

typedef struct {
	PChar path;
	PChar type;
	PFsNode root;
} FsMountPoint, *PFsMountPoint;

typedef struct {
	PChar name;
	Boolean (*probe)(PFsNode);
	PFsMountPoint (*mount)(PFsNode);
	Boolean (*umount)(PFsMountPoint);
} FsType, *PFsType;

Void DevFsInit(Void);

PList FsTokenizePath(PChar path);
PChar FsCanonicalizePath(PChar path);
PChar FsJoinPath(PChar src, PChar incr);
Boolean FsReadFile(PFsNode file, UIntPtr off, UIntPtr len, PUInt8 buf);
Boolean FsWriteFile(PFsNode file, UIntPtr off, UIntPtr len, PUInt8 buf);
PFsNode FsOpenFile(PChar path);
Void FsCloseFile(PFsNode node);
Boolean FsMountFile(PChar path, PChar file, PChar type);
Boolean FsUmountFile(PChar path);
PChar FsReadDirectoryEntry(PFsNode dir, UIntPtr entry);
PFsNode FsFindInDirectory(PFsNode dir, PChar name);
PFsMountPoint FsGetMountPoint(PChar path, PChar *outp);
PFsType FsGetType(PChar type);
Boolean FsAddMountPoint(PChar path, PChar type, PFsNode root);
Boolean FsRemoveMountPoint(PChar path);
Boolean FsAddType(PChar name, Boolean (*probe)(PFsNode), PFsMountPoint (*mount)(PFsNode), Boolean (*umount)(PFsMountPoint));
Boolean FsRemoveType(PChar name);
Void FsDbgListMountPoints(Void);
Void FsInit(Void);

#endif		// __CHICAGO_FILE_H__
