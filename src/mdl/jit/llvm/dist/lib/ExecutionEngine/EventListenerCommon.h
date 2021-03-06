//===-- JIT.h - Abstract Execution Engine Interface -------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Common functionality for JITEventListener implementations
//
//===----------------------------------------------------------------------===//

#ifndef EVENT_LISTENER_COMMON_H
#define EVENT_LISTENER_COMMON_H

#include "llvm/ADT/DenseMap.h"
#include "llvm/DebugInfo.h"
#include "llvm/IR/Metadata.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/ValueHandle.h"

namespace llvm {

namespace jitprofiling {

class FilenameCache {
  // Holds the filename of each Scope, so that we can pass a null-terminated
  // string into oprofile.  Use an AssertingVH rather than a ValueMap because we
  // shouldn't be modifying any MDNodes while this map is alive.
  DenseMap<AssertingVH<MDNode>, MISTD::string> Filenames;
  DenseMap<AssertingVH<MDNode>, MISTD::string> Paths;

 public:
  const char *getFilename(MDNode *Scope) {
    MISTD::string &Filename = Filenames[Scope];
    if (Filename.empty()) {
      DIScope DIScope(Scope);
      Filename = DIScope.getFilename();
    }
    return Filename.c_str();
  }

  const char *getFullPath(MDNode *Scope) {
    MISTD::string &P = Paths[Scope];
    if (P.empty()) {
      DIScope DIScope(Scope);
      StringRef DirName = DIScope.getDirectory();
      StringRef FileName = DIScope.getFilename();
      SmallString<256> FullPath;
      if (DirName != "." && DirName != "") {
        FullPath = DirName;
      }
      if (FileName != "") {
        sys::path::append(FullPath, FileName);
      }
      P = FullPath.str();
    }
    return P.c_str();
  }
};

} // namespace jitprofiling

} // namespace llvm

#endif //EVENT_LISTENER_COMMON_H
