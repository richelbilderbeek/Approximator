#ifndef TOOLTESTAPPROXIMATORMENUDIALOG_H
#define TOOLTESTAPPROXIMATORMENUDIALOG_H

#include "menudialog.h"


namespace ribi {
namespace tapx {

struct MenuDialog final : public ::ribi::MenuDialog
{
  MenuDialog();
  About GetAbout() const noexcept override;
  Help GetHelp() const noexcept override;
  std::string GetVersion() const noexcept override;
  std::vector<std::string> GetVersionHistory() const noexcept override;

  private:
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept override;
};

} //~namespace tapx
} //~namespace ribi

#endif // TOOLTESTAPPROXIMATORMENUDIALOG_H
