/////////////////////////////////////////////////////////////////////////////
// Authors:     Laurent Pugin and Rodolfo Zitellini
// Created:     2014
// Copyright (c) Authors and others. All rights reserved.
//
// Code generated using a modified version of libmei
// by Andrew Hankinson, Alastair Porter, and Others
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// NOTE: this file was generated with the Verovio libmei version and
// should not be edited because changes will be lost.
/////////////////////////////////////////////////////////////////////////////

#include "atts_facsimile.h"

//----------------------------------------------------------------------------

#include <cassert>

//----------------------------------------------------------------------------

namespace vrv {

//----------------------------------------------------------------------------
// AttFacsimile
//----------------------------------------------------------------------------

AttFacsimile::AttFacsimile() : Att()
{
    ResetFacsimile();
}

AttFacsimile::~AttFacsimile() {}

void AttFacsimile::ResetFacsimile()
{
    m_facs = "";
}

bool AttFacsimile::ReadFacsimile(pugi::xml_node element)
{
    bool hasAttribute = false;
    if (element.attribute("facs")) {
        this->SetFacs(StrToStr(element.attribute("facs").value()));
        element.remove_attribute("facs");
        hasAttribute = true;
    }
    return hasAttribute;
}

bool AttFacsimile::WriteFacsimile(pugi::xml_node element)
{
    bool wroteAttribute = false;
    if (this->HasFacs()) {
        element.append_attribute("facs") = StrToStr(this->GetFacs()).c_str();
        wroteAttribute = true;
    }
    return wroteAttribute;
}

bool AttFacsimile::HasFacs() const
{
    return (m_facs != "");
}

} // namespace

//----------------------------------------------------------------------------
// Module setter and getter
//----------------------------------------------------------------------------

#include "object.h"

//----------------------------------------------------------------------------

namespace vrv {

bool AttModule::SetFacsimile(Object *element, const std::string &attrType, const std::string &attrValue)
{
    if (element->HasAttClass(ATT_FACSIMILE)) {
        AttFacsimile *att = dynamic_cast<AttFacsimile *>(element);
        assert(att);
        if (attrType == "facs") {
            att->SetFacs(att->StrToStr(attrValue));
            return true;
        }
    }

    return false;
}

void AttModule::GetFacsimile(const Object *element, ArrayOfStrAttr *attributes)
{
    if (element->HasAttClass(ATT_FACSIMILE)) {
        const AttFacsimile *att = dynamic_cast<const AttFacsimile *>(element);
        assert(att);
        if (att->HasFacs()) {
            attributes->push_back({ "facs", att->StrToStr(att->GetFacs()) });
        }
    }
}

} // namespace
