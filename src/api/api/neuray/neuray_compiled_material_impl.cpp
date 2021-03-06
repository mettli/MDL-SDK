/***************************************************************************************************
 * Copyright (c) 2015-2018, NVIDIA CORPORATION. All rights reserved.
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
 **************************************************************************************************/

/** \file
 ** \brief Source for the ICompiled_material implementation.
 **/

#include "pch.h"

#include <mi/base/handle.h>

#include "neuray_compiled_material_impl.h"
#include "neuray_expression_impl.h"
#include "neuray_transaction_impl.h"
#include "neuray_value_impl.h"

#include <io/scene/mdl_elements/i_mdl_elements_compiled_material.h>
#include <io/scene/scene/i_scene_journal_types.h>

namespace MI {

namespace NEURAY {

DB::Element_base* Compiled_material_impl::create_db_element(
    mi::neuraylib::ITransaction* transaction,
    mi::Uint32 argc,
    const mi::base::IInterface* argv[])
{
    if( argc != 0)
        return 0;
    return new MDL::Mdl_compiled_material;
}

mi::base::IInterface* Compiled_material_impl::create_api_class(
    mi::neuraylib::ITransaction* transaction,
    mi::Uint32 argc,
    const mi::base::IInterface* argv[])
{
    if( argc != 0)
        return 0;
    return (new Compiled_material_impl())->cast_to_major();
}

mi::neuraylib::Element_type Compiled_material_impl::get_element_type() const
{
    return mi::neuraylib::ELEMENT_TYPE_COMPILED_MATERIAL;
}

const mi::neuraylib::IExpression_direct_call* Compiled_material_impl::get_body() const
{
   mi::base::Handle<Expression_factory> ef( get_transaction()->get_expression_factory());
   mi::base::Handle<const MDL::IExpression_direct_call> result_int( get_db_element()->get_body());
   return ef->create<mi::neuraylib::IExpression_direct_call>(
       result_int.get(), this->cast_to_major());
}

mi::Size Compiled_material_impl::get_temporary_count() const
{
    return get_db_element()->get_temporary_count();
}

const mi::neuraylib::IExpression* Compiled_material_impl::get_temporary(
    mi::Size index) const
{
   mi::base::Handle<Expression_factory> ef( get_transaction()->get_expression_factory());
   mi::base::Handle<const MDL::IExpression> result_int( get_db_element()->get_temporary( index));
   return ef->create( result_int.get(), this->cast_to_major());
}

mi::Float32 Compiled_material_impl::get_mdl_meters_per_scene_unit() const
{
    return get_db_element()->get_mdl_meters_per_scene_unit();
}

mi::Float32 Compiled_material_impl::get_mdl_wavelength_min() const
{
    return get_db_element()->get_mdl_wavelength_min();
}

mi::Float32 Compiled_material_impl::get_mdl_wavelength_max() const
{
    return get_db_element()->get_mdl_wavelength_max();
}

bool Compiled_material_impl::depends_on_state_transform() const
{
    return get_db_element()->depends_on_state_transform();
}

bool Compiled_material_impl::depends_on_state_object_id() const
{
    return get_db_element()->depends_on_state_object_id();
}

bool Compiled_material_impl::depends_on_global_distribution() const
{
    return get_db_element()->depends_on_global_distribution();
}

mi::Size Compiled_material_impl::get_parameter_count() const
{
    return get_db_element()->get_parameter_count();
}

const char* Compiled_material_impl::get_parameter_name( mi::Size index) const
{
    return get_db_element()->get_parameter_name( index);
}

const mi::neuraylib::IValue* Compiled_material_impl::get_argument( mi::Size index) const
{
   mi::base::Handle<Value_factory> vf( get_transaction()->get_value_factory());
   mi::base::Handle<const MDL::IValue> result_int( get_db_element()->get_argument( index));
   return vf->create( result_int.get(), this->cast_to_major());
}

mi::base::Uuid Compiled_material_impl::get_hash() const
{
    return get_db_element()->get_hash();
}

mi::base::Uuid Compiled_material_impl::get_slot_hash( mi::neuraylib::Material_slot slot) const
{
    return get_db_element()->get_slot_hash( slot);
}

const mi::neuraylib::IExpression* Compiled_material_impl::lookup_sub_expression(
    const char* path) const
{
    mi::base::Handle<Expression_factory> ef(
        get_transaction()->get_expression_factory());
    mi::base::Handle<const MDL::IExpression> result_int(
        get_db_element()->lookup_sub_expression( path));
    return ef->create( result_int.get(), this->cast_to_major());
}

const mi::neuraylib::IValue_list* Compiled_material_impl::get_arguments() const
{
    mi::base::Handle<Value_factory> vf( get_transaction()->get_value_factory());
    mi::base::Handle<const MDL::IValue_list> result_list( get_db_element()->get_arguments());
    return vf->create_value_list( result_list.get(), this->cast_to_major());
}

void Compiled_material_impl::swap( MDL::Mdl_compiled_material& rhs)
{
    get_db_element()->swap( rhs);
}

} // namespace NEURAY

} // namespace MI
