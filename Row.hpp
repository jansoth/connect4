#pragma once

/// @brief Hilfstyp um Row/Col nicht verwechseln zu können (Typsicherheit!!) 
struct Row {
    int value_;

    // Konstruktor implizit um Typumwandlung in int zu vermeiden
    explicit Row(int v) : value_{v} {}
};