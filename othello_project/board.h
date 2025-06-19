#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <random>
#include <algorithm>

// 각 칸의 상태를 나타내는 enum 클래스 (빈칸, 흑돌, 백돌, 장애물)
enum class CellState { Empty, Black, White, Obstacle };

// 게임 턴별 상태를 저장하는 구조체
struct GameTurn {
    std::vector<std::vector<CellState>> board_snapshot; // 현재 턴의 보드 상태 스냅샷
    int x, y;                 // 착수한 위치 (좌표)
    bool is_black_turn;       // 현재 턴이 흑돌 차례였는지 여부
    int total_black;          // 보드 위의 흑돌 개수
    int total_white;          // 보드 위의 백돌 개수
};

// 오델로 보드 클래스 선언
class Board {
public:
    Board(int size = 8);                         // 생성자: 보드 크기(기본 8x8)로 초기화
    void reset(int size);                        // 보드를 주어진 크기로 초기화

    CellState getCell(int x, int y) const;       // (x, y) 위치의 칸 상태 반환
    void setCell(int x, int y, CellState state); // (x, y) 위치에 상태 설정
    void set_board_state(const std::vector<std::vector<CellState>>& state); // 보드 전체 상태 설정
    int size() const;                            // 보드 크기 반환
    const std::vector<std::vector<CellState>>& getBoardState() const; // 현재 보드 상태 반환

    std::vector<std::pair<int,int>> getValidMoves(bool isBlackTurn) const; // 현재 플레이어의 착수 가능 위치 반환
    bool place_stone(int x, int y, bool isBlackTurn);   // (x, y)에 돌을 두고 뒤집기 처리, 성공 시 true 반환
    int flip_direction(int x, int y, int dx, int dy, CellState myColor, bool doFlip); // 한 방향에 대해 돌 뒤집기(또는 뒤집기 가능 여부만 검사)
    int count_stone(CellState color) const;             // 특정 색상의 돌 개수 반환

    void save_turn(int x, int y, bool isBlackTurn);     // 턴별 상태 저장 (리플레이/Undo용)
    const std::vector<GameTurn>& get_history() const;   // 저장된 턴 이력 반환
    void load_turn(int turn_idx);                       // 특정 턴으로 보드 상태 복원

    void place_obstacles(int obstacle_count);           // 보드에 장애물 배치
    void save_init_state(bool is_black_turn);           // 초기 상태 저장 (이어하기/리플레이용)
    void undo();                                       // Undo: 이전 턴 상태로 되돌리기

private:
    int m_board_size;                                  // 보드 크기 (ex: 8)
    std::vector<std::vector<CellState>> m_board_state; // 현재 보드의 칸 상태 정보
    std::vector<GameTurn> m_turn_history;              // 턴별 보드 상태 이력 (리플레이/Undo용)
};

#endif
