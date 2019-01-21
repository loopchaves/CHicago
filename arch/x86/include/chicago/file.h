// File author is Ítalo Lima Marconato Matias
//
// Created on July 16 of 2018, at 18:18 BRT
// Last edited on January 21 of 2018, at 11:54 BRT

#ifndef __CHICAGO_FILE_H__
#define __CHICAGO_FILE_H__

#include <chicago/device.h>
#include <chicago/list.h>

#define FS_FLAG_DIR 0x01
#define FS_FLAG_FILE 0x02

typedef struct FsNodeStruct {
	PChar name;
	PVoid priv;
	UIntPtr flags;
	UIntPtr inode;
	UIntPtr length;
	Boolean (*read)(struct FsNodeStruct *, UIntPtr, UIntPtr, PUInt8);
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
	PFsMountPoint (*mount)(PFsNode, PChar);
	Boolean (*umount)(PFsMountPoint);
} FsType, *PFsType;

Void DevFsInit(Void);
Void Iso9660Init(Void);

PList FsTokenizePath(PChar path);
PChar FsCanonicalizePath(PChar path);
PChar FsJoinPath(PChar src, PChar incr);
Boolean FsReadFile(PFsNode file, UIntPtr off, UIntPtr len, PUInt8 buf);
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
Boolean FsAddType(PChar name, Boolean (*probe)(PFsNode), PFsMountPoint (*mount)(PFsNode, PChar), Boolean (*umount)(PFsMountPoint));
Boolean FsRemoveType(PChar name);
Void FsInit(Void);

#endif		// __CHICAGO_FILE_H__
