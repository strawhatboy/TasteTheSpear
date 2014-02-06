//#include "IHasAnyKeyToContinue.h"
//
//
//IHasAnyKeyToContinue::IHasAnyKeyToContinue(void)
//{
//	INIT_POINTER(this->Finish);
//	INIT_POINTER(this->Continue);
//	this->EnableAnyKeyToContinue(false);
//}
//
//
//IHasAnyKeyToContinue::~IHasAnyKeyToContinue(void)
//{
//}
//
//void IHasAnyKeyToContinue::OnContinue(void)
//{
//	if (this->Continue)
//		(this->*Continue)();
//}
//
//void IHasAnyKeyToContinue::OnFinish(void)
//{
//	if (this->Finish)
//		(this->*Finish)();
//}
//
//void IHasAnyKeyToContinue::EnableAnyKeyToContinue(bool enabled)
//{
//	this->m_bAnyKeyToContinueEnabled = enabled;
//}
//
//void IHasAnyKeyToContinue::AddFinishListener(SEL_Finish finishListener)
//{
//	this->Finish = finishListener;
//}
//
//void IHasAnyKeyToContinue::AddContinueListener(SEL_Continue continueListener)
//{
//	this->Continue = continueListener;
//}
//
//bool IHasAnyKeyToContinue::IsAnyKeyToContinueEnabled()
//{
//	return this->m_bAnyKeyToContinueEnabled;
//}