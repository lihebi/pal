#define MAX_SCENES 300
#define MAX_OBJECTS 600
#define NUM_MAGIC_ELEMENTAL 5
#define MAX_ENEMIES_IN_TEAM 5
#define MAX_PLAYER_ROLES 6
#define MAX_PLAYER_EQUIPMENTS 6
#define MAX_PLAYER_MAGICS 32
#define MAX_PLAYABLE_PLAYER_ROLES 5
#define MAX_LEVELS 99
#define MAX_POISONS 16
#define MAX_INVENTORY 256
#define MAX_PLAYERS_IN_PARTY 3

typedef struct tagEventObject {
  short vanishTime;
  ushort x;
  ushort y;
  short layer;
  ushort triggerScript;
  ushort autoScript;
  short state;
  ushort triggerMode;
  ushort nSprite;
  ushort nSpriteFrame;
  ushort direction;
  ushort frameId;
  ushort spritePtrOffset;
  ushort nSpriteFrameAuto;
  ushort spriteFrameAutoCount;
} EventObject, *LpEventObject;
typedef struct tagScene {
  ushort mapId;
  ushort scriptOnEnter;
  ushort scriptOnTeleport;
  ushort eventObjectId;
} Scene, *LpScene;
typedef struct tagObjectPlayer {
  ushort reserved[2]; // always 0
  ushort scriptOnFriendDeath;
  ushort scriptOnDying;
} ObjectPlayer;
typedef struct tagObjectItem {
  ushort bitmapId;
  ushort price;
  ushort scriptOnUse;
  ushort scriptOnEquip;
  ushort scriptOnThrow;
  ushort flags;
} ObjectItem;
typedef struct tagObjectMagic {
  ushort magicId;
  ushort reserved1; // 0
  ushort scriptOnSuccess;
  ushort scriptOnUse;
  ushort reserved2; // 0
  ushort flags;
} ObjectMagic;
typedef struct tagObjectEnemy {
  ushort enemyId;
  ushort resistance;
  ushort scriptOnTurnStart;
  ushort scriptOnBattleEnd;
  ushort scriptOnReady;
} ObjectEnemy;
typedef struct tagObjectPoison {
  ushort poisonLevel;
  ushort color;
  ushort playerScript;
  ushort reserved;
  ushort enemyScript;
} ObjectPoison;
typedef struct tagObject {
  ushort data[6];
  ObjectPlayer player;
  ObjectItem item;
  ObjectMagic magic;
  ObjectEnemy enemy;
  ObjectPoison poison;
} Object, *LpObject;
typedef struct tagFiles {
  FILE *fpFBP;
  FILE *fpMGO;
  FILE *fpBALL;
  FILE *fpDATA;
  FILE *fpF;
  FILE *fpFIRE;
  FILE *fpRGM;
  FILE *fpSSS;
} Files, *LpFiles;
typedef struct tagScriptEntry {
  ushort operation;
  ushort operand[3];
} ScriptEntry, *LpScriptEntry;
typedef struct tagStore {
  ushort items[MAX_STORE_ITEM];
} Store, *LpStore;
typedef struct tagEnemy {
  ushort nIdleFrame;
  ushort nMagicFrame;
  ushort nAttackFrame;
  ushort idleAnimSpeed;
  ushort nActWaitFrame;
  ushort offsetY;
  ushort attackSound;
  ushort actionSound;
  ushort magicSound;
  ushort deathSound;
  ushort callSound;
  ushort health;
  ushort exp;
  ushort cash;
  ushort level;
  ushort magic;
  ushort magicRate;
  ushort attackEquivItem;
  ushort attackEquivItemRate;
  ushort stealItem;
  ushort nStealItem;
  ushort attackStrength;
  ushort defense;
  ushort dexterity;
  ushort fleeRate;
  ushort poisonResistance;
  ushort elemResistance[NUM_MAGIC_ELEMENTAL];
  ushort physicalResistance;
  ushort dualMove;
  ushort collectValue;
} Enemy, *LpEnemy;
typedef struct tagEnemyTeam {
  ushort enemies[MAX_ENEMIES_IN_TEAM];
} EnemyTeam, *LpEnemyTeam;
typedef ushort Players[MAX_PLAYER_ROLES];
typedef struct tagPlayerRoles {
  Players avatar;
  Players battleSpriteId; // in F.MKF
  Players spriteId; // in MGO.MKF
  Players name; // name of player class (in WORD.DATA)
  Players attackAll;
  Players unknown1;
  Players level;
  Players maxHP;
  Players maxMP;
  Players HP;
  Players MP;
  ushort equipment[MAX_PLAYER_EQUIPMENTS][MAX_PLAYER_ROLES];
  Players attackStrength;
  Players magicStrength;
  Players defense;
  Players dexterity;
  Players fleeRate;
  Players poisonResistance;
  ushort elementalResistance[NUM_MAGIC_ELEMENTAL][MAX_PLAYER_ROLES];
  Players unknown2;
  Players unknown3;
  Players unknown4;
  Players coveredBy;
  ushort magic[MAX_PLAYER_MAGICS][MAX_PLAYER_ROLES];
  Players walkFrames;
  Players cooperativeMagic;
  Players unknown5;
  Player unknown6;
  Players deathSound;
  Players attackSound;
  Players weaponSound;
  Players criticalSound;
  Players magicSound;
  Players coverSound;
  Players dyingSound;
} PlayerRoles, *LpPlayerRoles;
typedef struct tagMagic {
  ushort effect;
  ushort type;
  ushort offsetX;
  ushort offsetY;
  ushort summonEffect;
  ushort speed;
  ushort keepEffect;
  ushort soundDelay;
  ushort effectTimes;
  ushort shake;
  ushort wave;
  ushort unknown;
  ushort costMP;
  ushort baseDamage;
  ushort elemental;
  ushort sound;
} Magic, *LpMagic;
typedef struct tagBattleField {
  ushort screenWave;
  short magicEffect[NUM_MAGIC_ELEMENTAL];
} BattleField, *LpBattleField;
typedef struct tagLevelUpMagic {
  ushort level;
  ushort magic;
} LevelUpMagic, *LpLevelUpMagic;
typedef struct tagLevelUpMagicAll {
  LevelUpMagic m[MAX_PLAYABLE_PLAYER_ROLES];
} LevelUpMagicAll, *LpLevelUpMagicAll;
typedef struct tagEnemyPos {
  struct {
    ushort x;
    ushort y;
  } pos[MAX_ENEMIES_IN_TEAM][MAX_ENEMIES_IN_TEAM];
} EnemyPos, *LpEnemyPos;
typedef struct tagGameData {
  LpEventObject eventObject;
  int nEventObject;
  Scene scenes[MAX_SCENES];
  Object objects[Max_OBJECTS];
  LpScriptEntry scriptEntry;
  int nScriptEntry;
  LpStore store;
  int nStore;
  LpEnemy enemy;
  int nEnemy;
  LpEnemyTeam enemyTeam;
  int nEnemyTeam;
  PlayerRoles playerRoles;
  LpMagic magic;
  int nMagic;
  LpBattleField battleField;
  int nBattleField;
  LpLevelUpMagicAll levelUpMagic;
  int nLevelUpMagic;
  EnemyPos enemyPos;
  ushort levelUpExp[MAX_LEVELS + 1];
  ushort battleEffectIndex[10][2];
} GameData, *LpGameData;
typedef enum tagStatus {
  STATUS_CONFUSED = 0,
  STATUS_SLOW,
  STATUS_SLEEP,
  STATUS_SILENCE,
  STATUS_PUPPET,
  STATUS_BRAVERY,
  STATUS_PROTECT,
  STATUS_HASTE,
  STATUS_DUAL_ATTACK,
  STATUS_ALL
} STATUS;
typedef struct tagParty {
  ushort playerRole;
  short x,y;
  ushort frameId;
  ushort imageOffset;
} Party, *LpParty;
typedef struct tagTrail {
  ushort x,y;
  ushort direction;
} Trail, *LpTrail;
typedef struct tagExp {
  ushort exp;
  ushort reserved;
  ushort level;
  ushort count;
} Exp, *LpExp;
typedef struct tagAllExp {
  Exp primaryExp[MAX_PLAYER_ROLES];
  Exp healthExp[MAX_PLAYER_ROLES];
  Exp magicExp[MAX_PLAYER_ROLES];
  Exp attackExp[MAX_PLAYER_ROLES];
  Exp magicPowerExp[MAX_PLAYER_ROLES];
  Exp defenseExp[MAX_PLAYER_ROLES];
  Exp dexterityExp[MAX_PLAYER_ROLES];
  Exp fleeExp[MAX_PLAYER_ROLES];
} AllExp, *LpAllExp;
typedef struct tagPoisonStatus {
  ushort poisonId;
  ushort poisonScript;
} PoisonStatus, *LpPoisonStatus;
typedef struct tagGlobalVars {
  Files f;
  GameData g;
  char curSaveSlot;
  int curMainMenuItem;
  int curSystemMenuItem;
  int curInvMenuItem;
  int curPlayingRNG;
  bool gameStarted;
  bool enteringScene;
  bool needToFadeIn;
  bool inBattle;
  bool autoBattle;
  ushort lastUnequippedItem;
  PlayerRoles equipmentEffect[MAX_PLAYER_EQUIPMENTS + 1];
  ushort playerStatus[MAX_PLAYER_ROLES][STATUS_ALL];
  uint viewport; // pos
  uint partyOffset; // pos
  ushort layer;
  ushort maxPartyMemberIndex;
  Party party[MAX_PLAYABLE_PLAYER_ROLES];
  Trail trail[MAX_PLAYABLE_PLAYER_ROLES];
  ushort partyDirection;
  ushort sceneId;
  ushort paletteId;
  bool nightPalette;
  ushort musicId;
  ushort battleMusicId;
  ushort battleFieldId;
  ushort collectValue;
  ushort screenWave;
  short waveProgression;
  ushort chaseRange;
  ushort chaseSpeedChangeCycles;
  ushort nFollower;
  uint cash;
  AllExp exp;
  PoisonStatus poisonStatus[MAX_POISONS][MAX_PLAYABLE_PLAYER_ROLES];
  Inventory inventory[MAX_INVENTORY];
  uint frameId;
} GlobalVars, *LpGlobalVars;
