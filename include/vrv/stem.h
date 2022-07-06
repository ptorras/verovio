/////////////////////////////////////////////////////////////////////////////
// Name:        stem.h
// Author:      Laurent Pugin
// Created:     2017
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#ifndef __VRV_STEM_H__
#define __VRV_STEM_H__

#include "atts_cmn.h"
#include "atts_shared.h"
#include "atts_visual.h"
#include "layerelement.h"

namespace vrv {

class Flag;

//----------------------------------------------------------------------------
// Stem
//----------------------------------------------------------------------------

/**
 * This class models a stem as a layer element part and has not direct MEI equivlatent.
 */
class Stem : public LayerElement, public AttGraced, public AttStems, public AttStemsCmn {
public:
    /**
     * @name Constructors, destructors, reset and class name methods
     * Reset method resets all attribute classes
     */
    ///@{
    Stem();
    virtual ~Stem();
    void Reset() override;
    std::string GetClassName() const override { return "Stem"; }
    Object *Clone() const override { return new Stem(*this); }
    ///@}

    /** Override the method since alignment is required */
    bool HasToBeAligned() const override { return true; }

    /**
     * Add an element (only flag supported) to a stem.
     */
    bool IsSupportedChild(Object *object) override;

    /**
     * @name Setter and getter for darwing stem direction and length
     */
    ///@{
    data_STEMDIRECTION GetDrawingStemDir() const { return m_drawingStemDir; }
    void SetDrawingStemDir(data_STEMDIRECTION drawingStemDir) { m_drawingStemDir = drawingStemDir; }
    int GetDrawingStemLen() const { return m_drawingStemLen; }
    void SetDrawingStemLen(int drawingStemLen) { m_drawingStemLen = drawingStemLen; }
    int GetDrawingStemAdjust() const { return m_drawingStemAdjust; }
    void SetDrawingStemAdjust(int drawingStemAdjust) { m_drawingStemAdjust = drawingStemAdjust; }
    int GetStemModRelY() const { return m_stemModRelY; }
    ///@}

    /**
     * @name Setter and getter of the virtual flag
     */
    ///@{
    bool IsVirtual() const { return m_isVirtual; }
    void IsVirtual(bool isVirtual) { m_isVirtual = isVirtual; }
    ///@}

    /**
     * Helper to adjust overlaping layers for stems
     */
    int CompareToElementPosition(const Doc *doc, const LayerElement *otherElement, int margin) const;

    /**
     * Helper to calculate stem modifier relative Y rel and required adjustment for stem length
     */
    int CalculateStemModAdjustment(const Doc *doc, const Staff *staff, int flagOffset = 0);

    //----------//
    // Functors //
    //----------//

    /**
     * See Object::CalcStem
     */
    int CalcStem(FunctorParams *functorParams) override;

    /**
     * Overwritten version of Save that avoids anything to be written
     */
    ///@{
    int Save(FunctorParams *functorParams) override { return FUNCTOR_CONTINUE; }
    int SaveEnd(FunctorParams *functorParams) override { return FUNCTOR_CONTINUE; }
    ///@}

    /**
     * See Object::ResetData
     */
    int ResetData(FunctorParams *functorParams) override;

private:
    /**
     * Addjusts flag placement and stem length if they are crossing notehead or ledger lines
     */
    void AdjustFlagPlacement(const Doc *doc, Flag *flag, int staffSize, int verticalCenter, int duration);

    /**
     * Helper to adjust length of stem based on presence of slashes
     */
    int AdjustSlashes(const Doc *doc, const Staff *staff, int flagOffset) const;

    /**
     * Helper to calculate relative position for the stem modifier
     */
    void CalculateStemModRelY(const Doc *doc, const Staff *staff);

public:
    //
private:
    /**
     * The drawing direction of the stem
     */
    data_STEMDIRECTION m_drawingStemDir;
    /**
     * The drawing length of stem
     */
    int m_drawingStemLen;
    /**
     * Relative Y position for the stem modifier
     */
    int m_stemModRelY;
    /**
     * The adjustment of the drawing stem length (used with french style of beams)
     */
    int m_drawingStemAdjust;
    /**
     * A flag indicating if a stem if virtual and should never be rendered.
     * Virtual stems are added to whole notes (and longer) for position calculation and
     * for supporting MEI @stem.mod
     */
    bool m_isVirtual;
};

} // namespace vrv

#endif //__VRV_STEM_H__
