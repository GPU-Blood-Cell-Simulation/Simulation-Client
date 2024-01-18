#include "../../gui_controller.hpp"

#include <iostream>

#include <thread>
#include <sys/stat.h>

enum class Phase {
    before,
    inProgress,
    after
};

static struct {
    Phase init = Phase::before;
    Phase cloneRepo = Phase::before;
    Phase copyConfig = Phase::before;
    Phase cmakeConfigure = Phase::before;
    Phase compile = Phase::before;
} SimulationPhases;

static bool threadFinished = false;
static std::thread thread;
static int threadResult;


namespace gui
{
    static void cloneRepo()
    {
        struct stat sb;

        if (stat("Simulation-Server", &sb) == 0) {
            threadResult = system("cd Simulation-Server/ && git pull");
        }
        else {
            threadResult = system("git clone --branch PNieck/faster_streaming https://github.com/GPU-Blood-Cell-Simulation/Simulation-Server.git");
        }

        threadFinished = true;
    }


    static void copyConfig()
    {
        threadResult = system("cp -a ../SimulationGeneratedConfig/. Simulation-Server/src/config/");
        threadFinished = true;
    }


    static void configureCMake()
    {
        struct stat sb;

        if (stat("Simulation-Server", &sb) != 0) {
            threadResult = system("mkdir Simulation-Server/build/");
            if (threadResult != 0) {
                threadFinished = true;
                return;
            }
        }

        threadResult = system("cmake -S Simulation-Server/ -B Simulation-Server/build/ -D WINDOW_RENDERING=OFF -DCMAKE_BUILD_TYPE=Debug");
        threadFinished = true;
    }


    static void compileServer()
    {
        threadResult = system("cmake --build Simulation-Server/build/ --parallel 3 --target Simulation_server");
        threadFinished = true;
    }

    static void runServer()
    {
        system("cd Simulation-Server/build/ && ./Simulation_server");
    }


    void GUIController::renderLocalSimulation()
    {
        if (SimulationPhases.init == Phase::before) {

            std::cout << "Init Simulation Phase\n";
            SimulationPhases.init = Phase::after;
            SimulationPhases.cloneRepo = Phase::before;
            SimulationPhases.copyConfig = Phase::before;
            SimulationPhases.cmakeConfigure = Phase::before;
            SimulationPhases.compile = Phase::before;
        }

        if (SimulationPhases.cloneRepo == Phase::before) {
            std::cout << "Starting git thread\n";
            thread = std::thread(&cloneRepo);
            SimulationPhases.cloneRepo = Phase::inProgress;
        }

        else if (SimulationPhases.cloneRepo == Phase::inProgress && threadFinished == true) {
            std::cout << "Joining git thread\n";
            thread.join();
            threadFinished = false;
            SimulationPhases.cloneRepo = Phase::after;
            if (threadResult != 0) {
                setError("Error while cloning repo");
                setMode(Mode::mainScreen);
            } else {
                std::cout << "Successful repo clone\n";
            }
        }

        else if (SimulationPhases.cloneRepo == Phase::after && SimulationPhases.copyConfig == Phase::before) {
            std::cout << "Starting clone thread\n";
            thread = std::thread(&copyConfig);
            SimulationPhases.copyConfig = Phase::inProgress;
        }

        else if (SimulationPhases.copyConfig == Phase::inProgress && threadFinished == true) {
            std::cout << "Joining clone thread\n";
            thread.join();
            threadFinished = false;
            SimulationPhases.copyConfig = Phase::after;
            if (threadResult != 0) {
                setError("Error while copying config");
                setMode(Mode::mainScreen);
            } else {
                std::cout << "Successful copying config\n";
            }
        }

        else if (SimulationPhases.copyConfig == Phase::after && SimulationPhases.cmakeConfigure == Phase::before) {
            std::cout << "Starting configure cmake thread\n";
            thread = std::thread(&configureCMake);
            SimulationPhases.cmakeConfigure = Phase::inProgress;
        }

        else if (SimulationPhases.cmakeConfigure == Phase::inProgress && threadFinished == true) {
            std::cout << "Joining configure cmake thread\n";
            thread.join();
            threadFinished = false;
            SimulationPhases.cmakeConfigure = Phase::after;
            if (threadResult != 0) {
                setError("Error while configuring cmake");
                setMode(Mode::mainScreen);
            } else {
                std::cout << "Successful cmake configure\n";
            }
        }

        else if (SimulationPhases.cmakeConfigure == Phase::after && SimulationPhases.compile == Phase::before) {
            std::cout << "Starting compilation thread\n";
            thread = std::thread(&compileServer);
            SimulationPhases.compile = Phase::inProgress;
        }

        else if (SimulationPhases.compile == Phase::inProgress && threadFinished == true) {
            std::cout << "Joining compilation thread\n";
            thread.join();
            threadFinished = false;
            SimulationPhases.compile = Phase::after;
            if (threadResult != 0) {
                setError("Error while compiling");
                setMode(Mode::mainScreen);
            } else {
                std::cout << "Successful compile\n";
            }
        }

        else if (SimulationPhases.compile == Phase::after) {
            std::cout << "Starting run thread\n";
            thread = std::thread(&runServer);
            thread.detach();

            SimulationPhases.init = Phase::before;

            setMode(Mode::streamWatching);
        }
    }
}

