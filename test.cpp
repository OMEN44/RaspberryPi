#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;

class GameEngine
{
public:
    int t = 0;

    void update()
    {
        cout << "update" << t << endl;
        t++;
        // Your update logic here
        // This function will be executed in a loop until `running` is set to false
    }

    void runUpdateLoop(std::atomic<bool>& running)
    {
        while (running)
        {
            update();
            // You can add a delay here using std::this_thread::sleep_for if desired
        }
    }
};

int main()
{
    std::atomic<bool> running(true); // Atomic variable to control the loop

    GameEngine engine; // Create an instance of your game engine class

    std::thread t(&GameEngine::runUpdateLoop, &engine, std::ref(running)); // Start the thread, passing the running variable by reference

    // Wait for user input or any other condition to set `running` to false
    std::this_thread::sleep_for(std::chrono::seconds(5));

    running = false; // Set the condition to exit the loop

    t.join(); // Wait for the thread to finish

    return 0;
}