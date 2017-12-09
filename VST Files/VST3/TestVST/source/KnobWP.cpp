		#include "KnobWP.h"
#include "vstgui/lib/cbitmap.h"
#include <cmath>

/* ------------------------------------------------------
     CKnobWP
     Custom VSTGUI Object by Will Pirkle
     Created with RackAFX(TM) Plugin Development Software
     www.willpirkle.com
 -------------------------------------------------------*/

namespace VSTGUI {

CKnobWP::CKnobWP (const CRect& size, CControlListener* listener, int32_t tag, int32_t subPixmaps, CCoord heightOfOneImage, CBitmap* background, const CPoint &offset, bool bSwitchKnob)
: CAnimKnob (size, listener, tag, subPixmaps, heightOfOneImage, background, offset)
, m_bSwitchKnob(bSwitchKnob)
{
	m_fMaxValue = 1.0;
    m_bDraggingKnob = false;
}
CKnobWP::~CKnobWP(void)
{

}

CMouseEventResult CKnobWP::onMouseDown(CPoint& where, const CButtonState& buttons)
{
    m_bDraggingKnob = true;
    return CAnimKnob::onMouseDown(where, buttons);
}

CMouseEventResult CKnobWP::onMouseUp(CPoint& where, const CButtonState& buttons)
{
    m_bDraggingKnob = false;
    return CAnimKnob::onMouseUp(where, buttons);
}

void CKnobWP::draw(CDrawContext* pContext)
{
	if(getDrawBackground ())
	{
		CPoint where (0, 0);

		float fOldValue = value;

		// --- normalize to the switch for clicky behaviour
		if(m_bSwitchKnob)
		{
			// --- not used in VST3
			float fFlooredValue = getValueNormalized();
			fFlooredValue *= m_fMaxValue;
            fFlooredValue = floor(value + 0.5f);
			fFlooredValue /= m_fMaxValue;
			value = fFlooredValue;
		}

		if(value >= 0.f && heightOfOneImage > 0.)
		{
			CCoord tmp = heightOfOneImage * (getNumSubPixmaps () - 1);
			if (bInverseBitmap)
				where.y = floor ((1. - value) * tmp);
			else
				where.y = floor (value * tmp);
			where.y -= (int32_t)where.y % (int32_t)heightOfOneImage;
		}

		// --- draw it
		getDrawBackground()->draw(pContext, getViewSize(), where);

		value = fOldValue;
	}

	setDirty (false);
}


CMouseEventResult CKnobWP::onMouseMoved (CPoint& where, const CButtonState& buttons)
{
	CMouseEventResult res = CKnob::onMouseMoved(where, buttons);
	return res;
}

void CKnobWP::valueChanged()
{
	CAnimKnob::valueChanged();
}

void CKnobWP::setValue(float val)
{
	CAnimKnob::setValue(val);
}

}