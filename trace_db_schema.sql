
-- Table: IoStack
CREATE TABLE IoStack ( 
    Sequence   INTEGER PRIMARY KEY
                       NOT NULL,
    PushObject TEXT,
    SetMark    INTEGER,
    PopMark    INTEGER 
);


-- Table: IoCall
CREATE TABLE IoCall ( 
    Sequence INTEGER PRIMARY KEY
                     NOT NULL,
    Address  TEXT    NOT NULL,
    Message  TEXT 
);


-- Table: ObjectAllocation
CREATE TABLE ObjectAllocation ( 
    Sequence    INTEGER PRIMARY KEY
                        NOT NULL,
    Address     TEXT    NOT NULL,
    WhenFreed   INTEGER,
    Description TEXT 
);


-- Table: LMExpr
CREATE TABLE LMExpr ( 
    Sequence  INTEGER PRIMARY KEY
                      NOT NULL,
    Address   TEXT    NOT NULL,
    TypeIndex INTEGER NOT NULL
                      REFERENCES TypeIndex ( Id ),
    ValuePtr  TEXT    NOT NULL 
);


-- Table: LMTypeIndex
CREATE TABLE LMTypeIndex ( 
    Id          INTEGER PRIMARY KEY
                        NOT NULL,
    Description TEXT    NOT NULL 
);


-- Table: IoMessage
CREATE TABLE IoMessage ( 
    Sequence        INTEGER PRIMARY KEY
                            NOT NULL,
    Address         TEXT    NOT NULL,
    Name            TEXT,
    Label           TEXT,
    LineNumber      INTEGER,
    CharacterNumber INTEGER 
);


-- Table: IoObject
CREATE TABLE IoObject ( 
    Sequence  INTEGER NOT NULL,
    Address   TEXT    NOT NULL,
    IoTag     TEXT    NOT NULL,
    Data      TEXT,
    Proto     TEXT    NOT NULL,
    ProtoName TEXT    NOT NULL 
);


-- Table: IoTag
CREATE TABLE IoTag ( 
    Sequence INTEGER PRIMARY KEY
                     NOT NULL,
    Address  TEXT    NOT NULL,
    Name     TEXT    NOT NULL 
);


-- Table: Session
CREATE TABLE Session ( 
    StartTime DATETIME NOT NULL
                       DEFAULT ( CURRENT_TIMESTAMP ),
    Program   TEXT 
);

