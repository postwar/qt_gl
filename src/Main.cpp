#include "QtCore.hpp"

int main(int argc, char *argv[]) {
	QtCore m_Core(argc, argv);
	
	m_Core.Initialize();
	
	return m_Core.Run();
}
