#ifndef __cknobwp__
#define __cknobwp__
#include "vstgui/lib/controls/cknob.h"
#include <vector>
#include "vstgui4constants.h"

namespace VSTGUI {

/* ------------------------------------------------------
     CKnobWP
     Custom VSTGUI Object by Will Pirkle
     Created with RackAFX(TM) Plugin Development Software
     www.willpirkle.com
 -------------------------------------------------------*/

class CKnobWP : public CAnimKnob
{
public:
	CKnobWP(const CRect& size, CControlListener* listener, int32_t tag, int32_t subPixmaps,
			CCoord heightOfOneImage, CBitmap* background, const CPoint &offset,
			bool bSwitchKnob = false);

	virtual void draw (CDrawContext* pContext) VSTGUI_OVERRIDE_VMETHOD;
    bool m_bDraggingKnob;
   
    CMouseEventResult onMouseUp(CPoint& where, const CButtonState& buttons) VSTGUI_OVERRIDE_VMETHOD;
    CMouseEventResult onMouseDown(CPoint& where, const CButtonState& buttons) VSTGUI_OVERRIDE_VMETHOD;
	virtual CMouseEventResult onMouseMoved (CPoint& where, const CButtonState& buttons) VSTGUI_OVERRIDE_VMETHOD;
    
	virtual void valueChanged();
	virtual void setValue (float val);

	void setSwitchMax(float f){m_fMaxValue = f;}
	bool isSwitchKnob(){return m_bSwitchKnob;}

protected:
	bool m_bSwitchKnob;
	float m_fMaxValue;
	virtual ~CKnobWP(void);
};
}

#endif