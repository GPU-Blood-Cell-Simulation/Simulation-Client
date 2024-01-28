#include "../../gui_controller.hpp"

#include <iostream>

#include <thread>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <filesystem>
#include <atomic>


namespace gui
{
    enum class LocalSimPhase {
        init,

        beforeRepoClone,
        duringRepoClone,

        beforeConfigCopy,
        duringConfigCopy,

        beforeCMakeConfigure,
        duringCMakeConfigure,

        beforeCompilation,
        duringCompilation,

        beforeServerRun
    };

    static struct {
        LocalSimPhase phase = LocalSimPhase::init;

        std::atomic_bool threadFinished = false;
        std::thread thread;
        int threadResult;
    } LocalSimContext;


    static void cloneRepo()
    {
        struct stat sb;

        if (stat("Simulation-Server", &sb) == 0) {
            LocalSimContext.threadResult = system("cd Simulation-Server/ && git pull");
        }
        else {
            LocalSimContext.threadResult = system("git clone --branch dev https://github.com/GPU-Blood-Cell-Simulation/Simulation-Server.git");
        }

        LocalSimContext.threadFinished = true;
    }


    static void copyConfig()
    {
        LocalSimContext.threadResult = system("cp -a ../SimulationGeneratedConfig/. Simulation-Server/src/config/");
        LocalSimContext.threadFinished = true;
    }


    static void configureCMake()
    {
        struct stat sb;

        if (stat("Simulation-Server", &sb) != 0) {
            LocalSimContext.threadResult = system("mkdir Simulation-Server/build/");
            if (LocalSimContext.threadResult != 0) {
                LocalSimContext.threadFinished = true;
                return;
            }
        }

        LocalSimContext.threadResult = system("cmake -S Simulation-Server/ -B Simulation-Server/build/ -D WINDOW_RENDERING=OFF -DCMAKE_BUILD_TYPE=Debug");
        LocalSimContext.threadFinished = true;
    }


    static void compileServer()
    {
        LocalSimContext.threadResult = system("cmake --build Simulation-Server/build/ --parallel 3 --target Simulation_server");
        LocalSimContext.threadFinished = true;
    }

    static int runServer()
    {
        pid_t pid = fork();

        if (pid < 0)
            return -1; // Fork failed

        if (pid == 0) {
            // Child process
            auto currentPath = std::filesystem::current_path();
            auto serverBuildPath = currentPath / "Simulation-Server/build/";

            std::filesystem::current_path(serverBuildPath);
            execlp("./Simulation_server", "./Simulation_server", NULL);
        }

        // Parent process
        return 0;
    }


    void GUIController::renderLocalSimulation()
    {
        switch (LocalSimContext.phase)
        {
            case LocalSimPhase::init:
                LocalSimContext.phase = LocalSimPhase::beforeRepoClone;
                break;

            case LocalSimPhase::beforeRepoClone:
                std::cout << "Starting git thread\n";
                LocalSimContext.threadFinished = false;
                LocalSimContext.thread = std::thread(&cloneRepo);
                LocalSimContext.phase = LocalSimPhase::duringRepoClone;
                break;

            case LocalSimPhase::duringRepoClone:
                if (LocalSimContext.threadFinished == true) {
                    LocalSimContext.thread.join();

                    if (LocalSimContext.threadResult != 0) {
                        setError("Error while cloning repo");
                        LocalSimContext.phase = LocalSimPhase::init;
                        setMode(Mode::mainScreen);
                    } else {
                        std::cout << "Successful repo clone\n";
                        LocalSimContext.phase = LocalSimPhase::beforeConfigCopy;
                    }
                }
                break;

            case LocalSimPhase::beforeConfigCopy:
                std::cout << "Starting clone thread\n";
                LocalSimContext.threadFinished = false;
                LocalSimContext.thread = std::thread(&copyConfig);
                LocalSimContext.phase = LocalSimPhase::duringConfigCopy;
                break;

            case LocalSimPhase::duringConfigCopy:
                if (LocalSimContext.threadFinished == true) {
                    LocalSimContext.thread.join();

                    if (LocalSimContext.threadResult != 0) {
                        setError("Error while copying config");
                        LocalSimContext.phase = LocalSimPhase::init;
                        setMode(Mode::mainScreen);
                    } else {
                        std::cout << "Successful config copy\n";
                        LocalSimContext.phase = LocalSimPhase::beforeCMakeConfigure;
                    }
                }
                break;

            case LocalSimPhase::beforeCMakeConfigure:
                std::cout << "Starting CMake configure thread\n";
                LocalSimContext.threadFinished = false;
                LocalSimContext.thread = std::thread(&configureCMake);
                LocalSimContext.phase = LocalSimPhase::duringCMakeConfigure;
                break;

            case LocalSimPhase::duringCMakeConfigure:
                if (LocalSimContext.threadFinished == true) {
                    LocalSimContext.thread.join();

                    if (LocalSimContext.threadResult != 0) {
                        setError("Error while configuring CMake");
                        LocalSimContext.phase = LocalSimPhase::init;
                        setMode(Mode::mainScreen);
                    } else {
                        std::cout << "Successful CMake configure\n";
                        LocalSimContext.phase = LocalSimPhase::beforeCompilation;
                    }
                }
                break;

            case LocalSimPhase::beforeCompilation:
                std::cout << "Starting compilation thread\n";
                LocalSimContext.threadFinished = false;
                LocalSimContext.thread = std::thread(&compileServer);
                LocalSimContext.phase = LocalSimPhase::duringCompilation;
                break;

            case LocalSimPhase::duringCompilation:
                if (LocalSimContext.threadFinished == true) {
                    LocalSimContext.thread.join();

                    if (LocalSimContext.threadResult != 0) {
                        setError("Error while configuring CMake");
                        LocalSimContext.phase = LocalSimPhase::init;
                        setMode(Mode::mainScreen);
                    } else {
                        std::cout << "Successful CMake configure\n";
                        LocalSimContext.phase = LocalSimPhase::beforeServerRun;
                    }
                }
                break;

            case LocalSimPhase::beforeServerRun:
                std::cout << "Starting simulation process\n";
                LocalSimContext.phase = LocalSimPhase::init;
                if (runServer() < 0) {
                    setError("Erro while creating simulation process");
                    setMode(Mode::mainScreen);
                }

                setMode(Mode::streamWatching);
                glController.setMode(graphics::Mode::Simulation);
                break;
        }
    }
}

