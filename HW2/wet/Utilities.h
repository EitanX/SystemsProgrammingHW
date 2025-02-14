
#pragma once

enum class MatamErrorType {
    UnmatchedSizes,
    OutOfBounds
};

void exitWithError(MatamErrorType error);
