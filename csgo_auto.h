#include <windows.h>
#include<string>

class auto_accepter {
public:
    void Start(); //starts the cycle

    auto_accepter() = default;
    auto_accepter(const auto_accepter&) = delete;
    auto_accepter(auto_accepter&&) = delete;

    auto_accepter& operator=(const auto_accepter&) = delete;
    auto_accepter& operator=(auto_accepter&&) = delete;

    ~auto_accepter() = default;

private:
    const DWORD needed_button_colour = 6212442; //green colour indicates that the game is ready to be accepted

    const std::string bot_api_key = "1214313916:AAFbt1Gg5W-BDblS7q8HdYQkgNDplfm_d-Y";

    DWORD button_width = 513, button_height = 414; //513,414 is ONLY for 1024x768
    DWORD window_width = 0, window_height = 0;

    unsigned int user_id = 0;

    void GetWindowResolution(); //get and set current window resolution
    void CalculateButtonCoordinates(); //calculates button coordinates in current window
    void GetCursorPosition(DWORD&, DWORD&); //get cursor coordinates 
    void SimMouseClick(); //simulates mouse click
    void GetUserId(); //Retrieves user id from file if it exists
    void SendMessageViaScript(); //Runs python script which send notification to user

    bool CheckIfButtonReady(); //Checks is button ready or not
};