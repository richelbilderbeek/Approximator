//---------------------------------------------------------------------------
/*
TestApproximator, tests the Approximator class
Copyright (C) 2013-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestApproximator.htm
//---------------------------------------------------------------------------
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
