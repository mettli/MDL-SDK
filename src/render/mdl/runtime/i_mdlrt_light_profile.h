/******************************************************************************
 * Copyright (c) 2014-2018, NVIDIA CORPORATION. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of NVIDIA CORPORATION nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/
/** \file
 ** \brief
 **/

#ifndef RENDER_MDL_RUNTIME_I_MDLRT_LIGHT_PROFILE_H
#define RENDER_MDL_RUNTIME_I_MDLRT_LIGHT_PROFILE_H

#include <mi/neuraylib/typedefs.h>

#include <base/data/db/i_db_tag.h>
#include <base/data/db/i_db_access.h>
#include <io/scene/lightprofile/i_lightprofile.h>

namespace MI {

namespace DB { class Transaction; }

namespace MDLRT {

class Light_profile
{
public:
    typedef DB::Typed_tag<LIGHTPROFILE::Lightprofile> Tag_type;

    Light_profile();

    Light_profile(Tag_type const &tag, DB::Transaction *trans);

    float get_power() const { return m_light_profile->get_power(); }

    float get_maximum() const { return m_light_profile->get_maximum(); }

    bool is_valid() const { return m_light_profile->is_valid(); }

protected:
    DB::Access<LIGHTPROFILE::Lightprofile>  m_light_profile;   // the underlying light profile
};

}  // MDLRT
}  // MI

#endif //RENDER_MDL_RUNTIME_I_MDLRT_LIGHT_PROFILE_H
