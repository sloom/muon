#include "chrome/browser/infobars/infobar_service.h"

#include "components/infobars/core/confirm_infobar_delegate.h"
#include "components/infobars/core/infobar.h"

std::unique_ptr<infobars::InfoBar> InfoBarService::CreateConfirmInfoBar(
    std::unique_ptr<ConfirmInfoBarDelegate> delegate) {
  delegate->Cancel();
}
