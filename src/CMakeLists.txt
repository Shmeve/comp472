set(SOURCE_FILES
    # Source files here...
    main.cpp
    AIPlayer.cpp
    AIPlayer.h
    Board.cpp
    Board.h
    GameManager.cpp
    GameManager.h
    HumanPlayer.cpp
    HumanPlayer.h
    Move.h
    NaivePlayer.cpp
    NaivePlayer.h
    Node.cpp
    Node.h
    RemainingTilesPlayer.cpp
    RemainingTilesPlayer.h
    Player.h
    UI.cpp
    UI.h
    PlayerFactory.h
    PlayerFactory.cpp)

# Create the console game executable
add_executable(comp472 ${SOURCE_FILES})

# Link required libraries
target_link_libraries(comp472 ${LIBRARIES})

# Mark this directory as a root directory for future includes
target_include_directories(comp472 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
