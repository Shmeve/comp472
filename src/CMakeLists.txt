set(SOURCE_FILES
    # Source files here...
    main.cpp
    Player/AIPlayer.cpp
    Player/AIPlayer.h
    Board.cpp
    Board.h
    Player/CellMovesPlayer.cpp
    Player/CellMovesPlayer.h
    GameManager.cpp
    GameManager.h
    Player/HumanPlayer.cpp
    Player/HumanPlayer.h
    Move.h
    Player/NaivePlayer.cpp
    Player/NaivePlayer.h
    Node.cpp
    Node.h
    Player/RemainingTilesPlayer.cpp
    Player/RemainingTilesPlayer.h
    Player/Player.h
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
