#ifndef QTTOOLTESTAPPROXIMATORMENUDIALOG_H
#define QTTOOLTESTAPPROXIMATORMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtToolTestApproximatorMenuDialog;
}

namespace ribi {
namespace tapx {

class QtMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtMenuDialog(QWidget *parent = 0) noexcept;
  QtMenuDialog(const QtMenuDialog&) = delete;
  QtMenuDialog& operator=(const QtMenuDialog&) = delete;
  ~QtMenuDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent * event) noexcept;

private:
  Ui::QtToolTestApproximatorMenuDialog *ui;

private slots:
  void on_button_about_clicked() noexcept;
  void on_button_quit_clicked() noexcept;
  void on_button_start_xy_clicked() noexcept;
  void on_button_start_xyz_clicked() noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace tapx
} //~namespace ribi

#endif // QTTOOLTESTAPPROXIMATORMENUDIALOG_H
