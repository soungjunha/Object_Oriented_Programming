#include "board.h"

// 8방향 (상,하,좌,우,대각선) 방향 벡터 (dx, dy)
const int dir[8][2] = { {0,1},{1,0},{0,-1},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1} };

// Board 클래스 생성자: 주어진 크기로 보드 초기화
Board::Board(int size) { reset(size); }

// 보드를 size x size 크기로 초기화하고 중앙에 기본 돌 배치
void Board::reset(int size) {
    m_board_size = size;    // 보드 크기 저장
    m_board_state.assign(size, std::vector<CellState>(size, CellState::Empty)); // 모든 칸 비움
    m_turn_history.clear(); // 이력(리플레이/Undo) 초기화

    int mid = size / 2;
    // 중앙 4칸에 흑/백 돌 배치 (오델로 기본 시작)
    m_board_state[mid-1][mid-1] = CellState::White;
    m_board_state[mid][mid]     = CellState::White;
    m_board_state[mid-1][mid]   = CellState::Black;
    m_board_state[mid][mid-1]   = CellState::Black;
}

// 최초 게임 상태(장애물까지 포함) 저장 (리플레이/이어하기 시작점)
void Board::save_init_state(bool is_black_turn) {
    GameTurn init_turn;
    init_turn.board_snapshot = m_board_state;  // 현재 보드 상태 복사
    init_turn.x = -1;                          // 첫턴(착수 없음 표시)
    init_turn.y = -1;
    init_turn.is_black_turn = is_black_turn;   // 현재 턴 정보
    m_turn_history.push_back(init_turn);       // 이력에 추가
}

// (x, y) 위치의 셀 상태 반환
CellState Board::getCell(int x, int y) const { return m_board_state[x][y]; }
// (x, y) 위치의 셀 상태 설정
void Board::setCell(int x, int y, CellState state) { m_board_state[x][y] = state; }
// 현재 보드 크기 반환
int Board::size() const { return m_board_size; }
// 전체 보드 상태 반환(2차원 벡터)
const std::vector<std::vector<CellState>>& Board::getBoardState() const { return m_board_state; }

// 현재 플레이어 기준으로 착수 가능한 위치(리스트) 반환
std::vector<std::pair<int,int>> Board::getValidMoves(bool isBlackTurn) const {
    std::vector<std::pair<int,int>> moves; // 착수 가능 위치 저장
    CellState myColor = isBlackTurn ? CellState::Black : CellState::White; // 내 돌 색
    CellState oppColor = isBlackTurn ? CellState::White : CellState::Black; // 상대 돌 색

    // 모든 칸 검사
    for (int i = 0; i < m_board_size; ++i) {
        for (int j = 0; j < m_board_size; ++j) {
            if (m_board_state[i][j] != CellState::Empty) continue; // 빈칸만 검사

            // 8방향 모두 검사
            for (int d = 0; d < 8; ++d) {
                int ni = i + dir[d][0], nj = j + dir[d][1];
                int cnt = 0;
                // 인접한 상대 돌 연속 탐색
                while (ni >= 0 && ni < m_board_size && nj >= 0 && nj < m_board_size
                       && m_board_state[ni][nj] == oppColor) {
                    ni += dir[d][0]; nj += dir[d][1]; cnt++;
                    // 범위 밖 or 내 돌/빈칸 만남
                    if (ni < 0 || ni >= m_board_size || nj < 0 || nj >= m_board_size) break;
                    // 내 돌을 만났고 상대 돌을 최소 1개 이상 감쌈 → 착수 가능
                    if (m_board_state[ni][nj] == myColor && cnt > 0) {
                        moves.push_back({i, j});
                        goto nextcell; // 한 방향이라도 되면 착수 가능
                    }
                }
            }
        nextcell:; // 다음 칸 검사
        }
    }
    return moves;
}

// (x, y)에 돌을 두고 뒤집기까지 처리, 성공 시 true/실패 시 false
bool Board::place_stone(int x, int y, bool isBlackTurn) {
    if (m_board_state[x][y] != CellState::Empty) return false; // 이미 놓임
    CellState myColor = isBlackTurn ? CellState::Black : CellState::White;
    bool canFlip = false;
    // 8방향 중 한 방향이라도 뒤집을 수 있으면 착수 가능
    for (int d = 0; d < 8; ++d)
        if (flip_direction(x, y, dir[d][0], dir[d][1], myColor, false) > 0) canFlip = true;
    if (!canFlip) return false; // 한 방향도 못 뒤집으면 착수 불가

    m_board_state[x][y] = myColor; // 내 돌 착수

    // 실제로 뒤집기 수행
    for (int d = 0; d < 8; ++d)
        flip_direction(x, y, dir[d][0], dir[d][1], myColor, true);
    return true;
}

// 한 방향(dx, dy)에 대해 뒤집기 가능 여부 or 실제 뒤집기 처리
int Board::flip_direction(int x, int y, int dx, int dy, CellState myColor, bool doFlip) {
    int i = x + dx, j = y + dy;
    CellState oppColor = (myColor == CellState::Black ? CellState::White : CellState::Black);
    int cnt = 0;
    // 인접한 상대 돌 연속 탐색
    while (i >= 0 && i < m_board_size && j >= 0 && j < m_board_size && m_board_state[i][j] == oppColor) {
        i += dx; j += dy; cnt++;
    }
    if (cnt == 0) return 0; // 인접 상대 돌 없음 → X
    if (i < 0 || i >= m_board_size || j < 0 || j >= m_board_size) return 0; // 범위 밖 → X
    if (m_board_state[i][j] != myColor) return 0; // 마지막에 내 돌이 아님 → X

    // doFlip==true면 실제로 돌 뒤집기 수행
    if (doFlip) {
        i = x + dx; j = y + dy;
        for (int k = 0; k < cnt; ++k) {
            m_board_state[i][j] = myColor;
            i += dx; j += dy;
        }
    }
    return cnt; // 뒤집은(혹은 뒤집을 수 있는) 돌 개수 반환
}

// 특정 색 돌 개수 카운트
int Board::count_stone(CellState color) const {
    int cnt = 0;
    for (const auto& row : m_board_state)
        for (CellState s : row) if (s == color) ++cnt;
    return cnt;
}

// 현재 턴 상태(좌표/보드/돌 개수 등) 저장 (리플레이/Undo용)
void Board::save_turn(int x, int y, bool is_black_turn) {
    GameTurn turn;
    turn.board_snapshot = m_board_state;   // 보드 복사
    turn.x = x;                            // 착수 위치
    turn.y = y;
    turn.is_black_turn = is_black_turn;    // 턴 정보
    turn.total_black = count_stone(CellState::Black); // 흑돌 수
    turn.total_white = count_stone(CellState::White); // 백돌 수
    m_turn_history.push_back(turn);        // 이력에 추가
}

// 저장된 턴 이력(리플레이/Undo) 반환
const std::vector<GameTurn>& Board::get_history() const { return m_turn_history; }

// 지정 턴 인덱스의 보드 상태로 복원
void Board::load_turn(int turn_idx) {
    if (turn_idx < 0 || turn_idx >= m_turn_history.size()) return;
    m_board_state = m_turn_history[turn_idx].board_snapshot;
}

// 장애물 개수만큼 보드에 랜덤 대칭 배치
void Board::place_obstacles(int obstacle_count) {
    std::vector<std::pair<int, int>> candidates;
    int mid = m_board_size / 2;

    // 상하 대칭 후보 생성 (중앙 4칸 및 대칭칸 제외)
    for (int i = 0; i < m_board_size / 2; ++i) { // 절반 행만
        for (int j = 0; j < m_board_size; ++j) {
            int sym_i = m_board_size - 1 - i;
            // 중앙 4칸, 그 대칭칸이면 제외
            bool is_center =
                ((i == mid || i == mid - 1) && (j == mid || j == mid - 1)) ||
                ((sym_i == mid || sym_i == mid - 1) && (j == mid || j == mid - 1));
            if (is_center) continue;
            // 둘 다 빈칸이어야 후보
            if (m_board_state[i][j] == CellState::Empty &&
                m_board_state[sym_i][j] == CellState::Empty) {
                candidates.push_back({i, j});
            }
        }
    }

    // 후보 좌표 랜덤 셔플
    std::shuffle(candidates.begin(), candidates.end(), std::mt19937(std::random_device()()));

    // 장애물 쌍 개수만큼 배치 (짝수만큼 대칭)
    int max_pairs = obstacle_count / 2;
    int count = 0;
    for (int k = 0; k < (int)candidates.size() && count < max_pairs; ++k) {
        int x = candidates[k].first;
        int y = candidates[k].second;
        int sym_x = m_board_size - 1 - x;
        m_board_state[x][y] = CellState::Obstacle;
        m_board_state[sym_x][y] = CellState::Obstacle;
        count++;
    }

    // 장애물 개수가 홀수면 중앙 가로줄 빈칸에 추가
    if (obstacle_count % 2 == 1) {
        int center_row = m_board_size / 2;
        for (int j = 0; j < m_board_size; ++j) {
            bool is_center = (center_row == mid || center_row == mid - 1) && (j == mid || j == mid - 1);
            if (is_center) continue;
            if (m_board_state[center_row][j] == CellState::Empty) {
                m_board_state[center_row][j] = CellState::Obstacle;
                break;
            }
        }
    }
}

// 외부에서 전체 보드 상태 직접 설정(불러오기/리플레이 등)
void Board::set_board_state(const std::vector<std::vector<CellState>>& state) {
    m_board_state = state;
}

// Undo 기능: 두 턴 전 상태로 복원 (자신의 직전 착수로 롤백)
void Board::undo() {
    if (m_turn_history.size() > 2) {
        m_turn_history.pop_back(); // 1턴 전 삭제
        m_turn_history.pop_back(); // 2턴 전 삭제
        const auto& prev = m_turn_history.back(); // 두 턴 전 상태로 복원
        m_board_state = prev.board_snapshot;
    }
}
