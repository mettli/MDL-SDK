//=====-- NVPTXSubtarget.h - Define Subtarget for the NVPTX ---*- C++ -*--====//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the NVPTX specific subclass of TargetSubtarget.
//
//===----------------------------------------------------------------------===//

#ifndef NVPTXSUBTARGET_H
#define NVPTXSUBTARGET_H

#include "NVPTX.h"
#include "NVPTXUtilities.h"
#include "llvm/Target/TargetSubtargetInfo.h"

#define GET_SUBTARGETINFO_HEADER
#include "NVPTXGenSubtargetInfo.inc"

#include <string>

namespace llvm {

class NVPTXSubtarget : public NVPTXGenSubtargetInfo {
  virtual void anchor();
  MISTD::string TargetName;
  NVPTX::DrvInterface drvInterface;
  bool Is64Bit;

  // PTX version x.y is represented as 10*x+y, e.g. 3.1 == 31
  unsigned PTXVersion;

  // SM version x.y is represented as 10*x+y, e.g. 3.1 == 31
  unsigned int SmVersion;

  mutable NVVMAnnotations Annos;

public:
  /// This constructor initializes the data members to match that
  /// of the specified module.
  ///
  NVPTXSubtarget(const MISTD::string &TT, const MISTD::string &CPU,
                 const MISTD::string &FS, bool is64Bit);

  bool hasBrkPt() const { return SmVersion >= 11; }
  bool hasAtomRedG32() const { return SmVersion >= 11; }
  bool hasAtomRedS32() const { return SmVersion >= 12; }
  bool hasAtomRedG64() const { return SmVersion >= 12; }
  bool hasAtomRedS64() const { return SmVersion >= 20; }
  bool hasAtomRedGen32() const { return SmVersion >= 20; }
  bool hasAtomRedGen64() const { return SmVersion >= 20; }
  bool hasAtomAddF32() const { return SmVersion >= 20; }
  bool hasVote() const { return SmVersion >= 12; }
  bool hasDouble() const { return SmVersion >= 13; }
  bool reqPTX20() const { return SmVersion >= 20; }
  bool hasF32FTZ() const { return SmVersion >= 20; }
  bool hasFMAF32() const { return SmVersion >= 20; }
  bool hasFMAF64() const { return SmVersion >= 13; }
  bool hasLDG() const { return SmVersion >= 32; }
  bool hasLDU() const { return ((SmVersion >= 20) && (SmVersion < 30)); }
  bool hasGenericLdSt() const { return SmVersion >= 20; }
  inline bool hasHWROT32() const { return SmVersion >= 32; }
  inline bool hasSWROT32() const {
    return ((SmVersion >= 20) && (SmVersion < 32));
  }
  inline bool hasROT32() const { return hasHWROT32() || hasSWROT32(); }
  inline bool hasROT64() const { return SmVersion >= 20; }

  bool hasImageHandles() const {
    // Enable handles for Kepler+, where CUDA supports indirect surfaces and
    // textures
    if (getDrvInterface() == NVPTX::CUDA)
      return (SmVersion >= 30);

    // Disabled, otherwise
    return false;
  }
  bool is64Bit() const { return Is64Bit; }

  unsigned int getSmVersion() const { return SmVersion; }
  NVPTX::DrvInterface getDrvInterface() const { return drvInterface; }
  MISTD::string getTargetName() const { return TargetName; }

  unsigned getPTXVersion() const { return PTXVersion; }

  void ParseSubtargetFeatures(StringRef CPU, StringRef FS);

  NVVMAnnotations &getNVVMAnnotations() const { return Annos; }
};

} // End llvm namespace

#endif // NVPTXSUBTARGET_H
