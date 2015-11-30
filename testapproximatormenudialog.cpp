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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "testapproximatormenudialog.h"

#include <cassert>
#include <iostream>

#include <boost/units/unit.hpp>
#include <boost/units/systems/si.hpp>

#include "approximator.h"
#include "canvas.h"
#include "drawcanvas.h"
#include "trace.h"
#include "testtimer.h"

#pragma GCC diagnostic pop

ribi::tapx::MenuDialog::MenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::tapx::MenuDialog::ExecuteSpecific(const std::vector<std::string>& /*argv*/) noexcept
{
  //Use Boost.Units to thoroughly check if Approximation is a good template:
  //If it even compiles with Boost.Units, it probably is
  {
    typedef boost::units::quantity<boost::units::si::time> Time;
    typedef boost::units::quantity<boost::units::si::velocity> Velocity;
    Approximator<Time,Velocity> a;
    a.Add(0.0 * boost::units::si::second,0.0 * boost::units::si::meters_per_second);
    a.Add(2.0 * boost::units::si::second,2.0 * boost::units::si::meters_per_second);
    #ifndef NDEBUG
    const Velocity v = a.Approximate(1.0 * boost::units::si::second);
    assert(v >= 0.99 * boost::units::si::meters_per_second
        && v <= 1.01 * boost::units::si::meters_per_second);
    #endif
  }

  typedef Approximator<double,int> Approximator_t;
  Approximator_t a;
  a.Add(20, 5);
  a.Add(30,15);
  a.Add(40, 5);
  a.Add(50,15);

  const int max_x = 78;
  const int max_y = 20;
  DrawCanvas c(
    max_x,
    max_y,
    CanvasColorSystem::invert,
    CanvasCoordinatSystem::graph
  );
  c.DrawLine(0.0,0.0,max_x,0.0);
  c.DrawLine(0.0,0.0,0.0,max_y);

  //Plot values (note: these won't be visible in Canvas)
  {
    std::vector<double> xs;
    std::vector<double> ys;
    for (const auto& p: a.Get())
    {
      c.DrawDot(
        static_cast<double>(p.first),
        static_cast<double>(p.second)
      );
    }
  }

  //Plot approximation
  {
    for (int t=0; t != max_x; ++t)
    {
      try
      {
        const double x = static_cast<double>(t);
        const double y = a.Approximate(x);
        c.DrawDot(x,y);
      }
      catch (ExceptionNoExtrapolation<Approximator_t::key_type>& e)
      {
        //X value not in range. OK not to plot then...
      }
    }
  }
  std::cout << c << std::endl;
  return 0;
}

ribi::About ribi::tapx::MenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestApproximator",
    "tests the Approximator class",
    "November 30th of 2015",
    "2013-2015",
    "http://www.richelbilderbeek.nl/ToolTestApproximator.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("Approximator version: " + Approximator<>::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::tapx::MenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    },
    {

    }
  );
}

std::string ribi::tapx::MenuDialog::GetVersion() const noexcept
{
  return "2.0";
}

std::vector<std::string> ribi::tapx::MenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-08-28: version 1.0: initial version",
    "2013-09-05: version 1.1: transition to namespace ribi",
    "2013-11-05: version 1.2: conformized for ProjectRichelBilderbeekConsole",
    "2015-11-31: version 2.0: moved to own GitHub",
  };
}

#ifndef NDEBUG
void ribi::tapx::MenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    Approximator<int,int>::Test();

  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
