# 水管工遊戲專案

## 專案介紹
水管工是一款經典的電腦遊戲，玩家的目標是透過旋轉並連接不同的水管片段，以形成一條從起點到終點的完整水管路徑。玩家需要不斷嘗試和調整，直到找出正確的水管組合，讓水流能夠順利通過，達成遊戲的勝利條件。

## 專案目錄結構
- `/exe`: 包含編譯後的可執行檔案以及使用說明的README文件。
- `/project`: 包含完整的開發專案，以便在任何電腦上進行編譯，附有說明專案編譯方式的README文件。
- `/src`: 包含所有源代碼的副本。
- `DEMO_VIDEO.mp4`: 影片檔案，展示遊戲玩法的示範。
- `工作分配表`: 記錄各組員的工作分配和貢獻比例。

## 評分標準

### 主要功能（70%）
- **讀取盤面（10%）**
- **生成隨機盤面（至少一組解）（20%）**
- **遊戲操作（20%）**
  - 旋轉水管（10%）
  - 透過按鍵移動選擇水管（5%）
  - 透過按鍵旋轉水管（5%）
- **通關判斷（20%）**
  - 單一路徑判斷（5%）
  - 任意連通路徑判斷（15%）

### 加分功能（最多40%）
- **隨機盤面生成（10%）**
- **M x N 盤面（M, N >= 3）（5%）**
- **在盤面四周隨機產生起點終點（5%）**
- **開發GUI（10%）**
- **GUI美觀（0~5%）**
- **動畫效果（5%）**
- **聲音效果（10%）**
  - BGM（5%）
  - 旋轉水管音效（5%）

### 防呆機制（每項扣10分）
- 指令在不正確的遊戲狀態下被執行（-10%）
- Row Col數字超出範圍（-10%）
- 未載入/生成盤面就執行開始遊戲（-10%）

## 使用說明

### 編譯專案
請參考`/project`目錄中的README。

### 遊戲操作
遊戲開始時，系統會自動生成一個隨機盤面。使用方向鍵移動選擇水管，並使用旋轉鍵進行旋轉。目標是連接起點和終點，形成一條完整的水管路徑。成功連通水管後，遊戲勝利。

## 開發者說明
詳細的開發文檔和代碼註解可以在`/src`目錄中找到。若有任何疑問或需要進一步的技術支持，請聯繫專案維護者。
