Aplikasi Visualisasi Pencarian Jalur (Pathfinder) - Kelompok 8
Selamat datang di repositori proyek kami. Aplikasi ini dikembangkan sebagai bagian dari tugas besar mata kuliah Struktur Data.

📝 Tentang Aplikasi Ini
Secara sederhana, program ini adalah simulasi visual yang menunjukkan bagaimana komputer "berpikir" untuk mencari jalan dari satu titik ke titik lain. Di balik layar, aplikasi ini menggunakan konsep-konsep pemrograman seperti Tree, Stack, dan Queue untuk menghitung rute, namun kami mengemasnya dalam tampilan grafis (Grid) agar mudah dipahami oleh siapa saja.

✨ Fitur Utama
Visualisasi Grid: Melihat area permainan dalam bentuk kotak-kotak (grid).
Pencarian Jalur: Demonstrasi algoritma pencarian jalan otomatis (Pathfinding) dengan Breadth First Search (BFS) atau Depth First Search (DFS).
Antarmuka Interaktif: Dilengkapi dengan menu dan efek suara sederhana, dan mode kuas untuk menginisialisasikan halangan (tembok).
Implementasi Struktur Data: Penerapan nyata dari teori struktur data (Tumpukan/Stack & Antrian/Queue) ke dalam sebuah program.

🖱️ Fitur Mouse
  -Klik kiri, berdasarkan mode kuas yang dipilih, maka akan melakukan inisialisasi status sel menjadi status tembok/start/end.
  -Klik kanan, untuk menghapus sel yang bernisialisasi Wall menjadi Idle.

⌨️ Fitur Keyboard
  -➡️ Tombol panah kanan untuk menjalankan 1 langkah terhadap algoritma yang dipilih (BFS/DFS).
  -Space untuk mulai dan berhenti jalnnya algoritma.
  -W untuk mengubah ke mode kuas menjadi kuas untuk tembok.
  -S untuk mengubah ke mode kuas menjadi kuas untuk mengatur posisi sel awal.
  -E untuk mengubah ke mode kuas menjadi kuas untuk mengatur posisi sel akhir.
  -R untuk mengatur ulang inisialisasi status sel, pohon, dan queue/stack.

🚀 Cara Menjalankan Aplikasi
Anda tidak perlu menginstal software pemrograman rumit untuk mencoba aplikasi ini. Cukup ikuti langkah berikut:
Pastikan Anda menggunakan sistem operasi Windows.
Buka folder bernama App.    
Cari file bernama main.exe.
Klik dua kali pada file tersebut untuk memulai program.

  
📂 Struktur Folder
Bagi yang tertarik dengan kode programnya, berikut penjelasan singkat isi folder kami:
App: Berisi aplikasi yang siap dijalankan beserta aset pendukung (suara & font).
Include: Berisi file header (.h) yang mendefinisikan struktur program.
Source: Berisi kode utama (.cpp) tempat logika program (seperti PathFinder, Grid, dll) bekerja.
