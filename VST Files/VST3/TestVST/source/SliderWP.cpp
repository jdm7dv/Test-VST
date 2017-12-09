#include "SliderWP.h"
#include "vstgui/lib/cbitmap.h"
#include "vstgui/lib/cdrawcontext.h"

#include <cmath>

/* ------------------------------------------------------
     CVerticalSliderWP, CHorizontalSliderWP
     Custom VSTGUI Objects by Will Pirkle
     Created with RackAFX(TM) Plugin Development Software
     www.willpirkle.com
 -------------------------------------------------------*/

namespace VSTGUI {

CVerticalSliderWP::CVerticalSliderWP(const CRect &rect, CControlListener* listener, int32_t tag, int32_t iMinPos, int32_t iMaxPos, CBitmap* handle, CBitmap* background, const CPoint& offset, const int32_t style)
: CVerticalSlider(rect, listener, tag, iMinPos, iMaxPos, handle, background, offset, style)
{
	m_bSwitchSlider = false;
	m_fMaxValue = 1.0;
    m_bDraggingSlider = false;
}

CVerticalSliderWP::~CVerticalSliderWP()
{

}

CMouseEventResult CVerticalSliderWP::onMouseDown(CPoint& where, const CButtonState& buttons)
{
    m_bDraggingSlider = true;
    return CVerticalSlider::onMouseDown(where, buttons);
}

CMouseEventResult CVerticalSliderWP::onMouseUp(CPoint& where, const CButtonState& buttons)
{
    m_bDraggingSlider = false;
    return CVerticalSlider::onMouseUp(where, buttons);
}

//------------------------------------------------------------------------
void CVerticalSliderWP::draw (CDrawContext *pContext)
{
	CDrawContext* drawContext = pContext;

	// draw background
	if (getDrawBackground ())
	{
		CRect rect (0, 0, widthControl, heightControl);
		rect.offset (getViewSize ().left, getViewSize ().top);
		getDrawBackground ()->draw (drawContext, rect, offset);
	}

	if (drawStyle != 0)
	{
		pContext->setDrawMode (kAliasing);
		pContext->setLineStyle (kLineSolid);
		pContext->setLineWidth (1.);
		if (drawStyle & kDrawFrame || drawStyle & kDrawBack)
		{
			pContext->setFrameColor (frameColor);
			pContext->setFillColor (backColor);
			CDrawStyle d = kDrawFilled;
			if (drawStyle & kDrawFrame && drawStyle & kDrawBack)
				d = kDrawFilledAndStroked;
			else if (drawStyle & kDrawFrame)
				d = kDrawStroked;
			pContext->drawRect (getViewSize (), d);
		}
		pContext->setDrawMode (kAntiAliasing);
		if (drawStyle & kDrawValue)
		{
			CRect r (getViewSize ());
			if (drawStyle & kDrawFrame)
				r.inset (1., 1.);

			float drawValue = getValueNormalized ();

			if (drawStyle & kDrawValueFromCenter)
			{
				if (drawStyle & kDrawInverted)
					drawValue = 1.f - drawValue;
				if (getStyle () & kHorizontal)
				{
					CCoord width = r.getWidth ();
					r.right = r.left + r.getWidth () * drawValue;
					r.left += width / 2.;
					r.normalize ();
				}
				else
				{
					CCoord height = r.getHeight ();
					r.bottom = r.top + r.getHeight () * drawValue;
					r.top += height / 2.;
					r.normalize ();
				}
			}
			else
			{
				if (getStyle () & kHorizontal)
				{
					if (drawStyle & kDrawInverted)
						r.left = r.right - r.getWidth () * drawValue;
					else
						r.right = r.left + r.getWidth () * drawValue;
				}
				else
				{
					if (drawStyle & kDrawInverted)
						r.bottom = r.top + r.getHeight () * drawValue;
					else
						r.top = r.bottom - r.getHeight () * drawValue;
				}
			}
			pContext->setFillColor (valueColor);
			pContext->drawRect (r, kDrawFilled);
		}
	}

	if(pHandle)
	{
		// --- normalize to the switch for clicky behaviour
		float fOldValue = value;
		if(m_bSwitchSlider)
		{
			float fFlooredValue = getValueNormalized();
			fFlooredValue *= m_fMaxValue;
            fFlooredValue = floor(value + 0.5f);
			fFlooredValue /= m_fMaxValue;
			value = fFlooredValue;
		}

		float normValue = getValueNormalized ();
		if (style & kRight || style & kBottom)
			normValue = 1.f - normValue;

		// calc new coords of slider
		CRect rectNew;
		if (style & kHorizontal)
		{
			rectNew.top    = offsetHandle.y;
			rectNew.bottom = rectNew.top + heightOfSlider;

			rectNew.left   = offsetHandle.x + floor (normValue * rangeHandle);
			rectNew.left   = (rectNew.left < minTmp) ? minTmp : rectNew.left;

			rectNew.right  = rectNew.left + widthOfSlider;
			rectNew.right  = (rectNew.right > maxTmp) ? maxTmp : rectNew.right;
		}
		else
		{
			rectNew.left   = offsetHandle.x;
			rectNew.right  = rectNew.left + widthOfSlider;

			rectNew.top    = offsetHandle.y + floor (normValue * rangeHandle);
			rectNew.top    = (rectNew.top < minTmp) ? minTmp : rectNew.top;

			rectNew.bottom = rectNew.top + heightOfSlider;
			rectNew.bottom = (rectNew.bottom > maxTmp) ? maxTmp : rectNew.bottom;
		}
		rectNew.offset (getViewSize ().left, getViewSize ().top);

		// draw slider at new position
		pHandle->draw (drawContext, rectNew);
		value = fOldValue;
	}

	setDirty (false);
}

CHorizontalSliderWP::CHorizontalSliderWP (const CRect &rect, CControlListener* listener, int32_t tag, int32_t iMinPos, int32_t iMaxPos, CBitmap* handle, CBitmap* background, const CPoint& offset, const int32_t style)
: CHorizontalSlider(rect, listener, tag, iMinPos, iMaxPos, handle, background, offset, style)
{
	m_bSwitchSlider = false;
	m_fMaxValue = 1.0;
    m_bDraggingSlider = false;
}
CHorizontalSliderWP::~CHorizontalSliderWP()
{

}

CMouseEventResult CHorizontalSliderWP::onMouseDown(CPoint& where, const CButtonState& buttons)
{
    m_bDraggingSlider = true;
    return CHorizontalSlider::onMouseDown(where, buttons);
}

CMouseEventResult CHorizontalSliderWP::onMouseUp(CPoint& where, const CButtonState& buttons)
{
    m_bDraggingSlider = false;
    return CHorizontalSlider::onMouseUp(where, buttons);
}

void CHorizontalSliderWP::draw (CDrawContext *pContext)
{
	CDrawContext* drawContext = pContext;

	// draw background
	if (getDrawBackground ())
	{
		CRect rect (0, 0, widthControl, heightControl);
		rect.offset (getViewSize ().left, getViewSize ().top);
		getDrawBackground ()->draw (drawContext, rect, offset);
	}

	if (drawStyle != 0)
	{
		pContext->setDrawMode (kAliasing);
		pContext->setLineStyle (kLineSolid);
		pContext->setLineWidth (1.);
		if (drawStyle & kDrawFrame || drawStyle & kDrawBack)
		{
			pContext->setFrameColor (frameColor);
			pContext->setFillColor (backColor);
			CDrawStyle d = kDrawFilled;
			if (drawStyle & kDrawFrame && drawStyle & kDrawBack)
				d = kDrawFilledAndStroked;
			else if (drawStyle & kDrawFrame)
				d = kDrawStroked;
			pContext->drawRect (getViewSize (), d);
		}
		pContext->setDrawMode (kAntiAliasing);
		if (drawStyle & kDrawValue)
		{
			CRect r (getViewSize ());
			if (drawStyle & kDrawFrame)
				r.inset (1., 1.);
			float drawValue = getValueNormalized ();
			if (drawStyle & kDrawValueFromCenter)
			{
				if (drawStyle & kDrawInverted)
					drawValue = 1.f - drawValue;
				if (getStyle () & kHorizontal)
				{
					CCoord width = r.getWidth ();
					r.right = r.left + r.getWidth () * drawValue;
					r.left += width / 2.;
					r.normalize ();
				}
				else
				{
					CCoord height = r.getHeight ();
					r.bottom = r.top + r.getHeight () * drawValue;
					r.top += height / 2.;
					r.normalize ();
				}
			}
			else
			{
				if (getStyle () & kHorizontal)
				{
					if (drawStyle & kDrawInverted)
						r.left = r.right - r.getWidth () * drawValue;
					else
						r.right = r.left + r.getWidth () * drawValue;
				}
				else
				{
					if (drawStyle & kDrawInverted)
						r.bottom = r.top + r.getHeight () * drawValue;
					else
						r.top = r.bottom - r.getHeight () * drawValue;
				}
			}
			pContext->setFillColor (valueColor);
			pContext->drawRect (r, kDrawFilled);
		}
	}

	if(pHandle)
	{
		// --- normalize to the switch for clicky behaviour
		float fOldValue = value;
		if(m_bSwitchSlider)
		{
			float fFlooredValue = getValueNormalized();
			fFlooredValue *= m_fMaxValue;
            fFlooredValue = floor(value + 0.5f);
			fFlooredValue /= m_fMaxValue;
			value = fFlooredValue;
		}

		float normValue = getValueNormalized ();
		if (style & kRight || style & kBottom)
			normValue = 1.f - normValue;

		// calc new coords of slider
		CRect rectNew;
		if (style & kHorizontal)
		{
			rectNew.top    = offsetHandle.y;
			rectNew.bottom = rectNew.top + heightOfSlider;

			rectNew.left   = offsetHandle.x + floor (normValue * rangeHandle);
			rectNew.left   = (rectNew.left < minTmp) ? minTmp : rectNew.left;

			rectNew.right  = rectNew.left + widthOfSlider;
			rectNew.right  = (rectNew.right > maxTmp) ? maxTmp : rectNew.right;
		}
		else
		{
			rectNew.left   = offsetHandle.x;
			rectNew.right  = rectNew.left + widthOfSlider;

			rectNew.top    = offsetHandle.y + floor (normValue * rangeHandle);
			rectNew.top    = (rectNew.top < minTmp) ? minTmp : rectNew.top;

			rectNew.bottom = rectNew.top + heightOfSlider;
			rectNew.bottom = (rectNew.bottom > maxTmp) ? maxTmp : rectNew.bottom;
		}
		rectNew.offset (getViewSize ().left, getViewSize ().top);

		// draw slider at new position
		pHandle->draw (drawContext, rectNew);
		value = fOldValue;
	}

	setDirty (false);
}

} // namespace
