#include <QApplication>

#include "adapter.h"
#include "view.h"

int main(int argc, char *argv[]) {
  QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
  QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
  QCoreApplication::setApplicationName(APPLICATION_NAME);
  QApplication a(argc, argv);
  View w;
  w.show();
  return a.exec();
}
