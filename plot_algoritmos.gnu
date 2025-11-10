# ==============================================
# Gráficos de Desempenho - Relatório Acadêmico
# Autor: Gleydson Rodrigues Lins
# ==============================================
# Estilo: Clean, Profissional e Científico
# ==============================================

set terminal pngcairo size 1280,640 enhanced font 'Arial,12'
set datafile separator whitespace

# Fundo branco e bordas limpas
set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb "#FFFFFF" behind
set border lw 1.2 lc rgb "#333333"
set grid xtics ytics lw 0.6 lc rgb "#CCCCCC"

# Escala dos eixos
set xrange [0:99000]
set yrange [0:*]

# Rótulos e títulos dos eixos
set xlabel "Tamanho do Vetor (N)" font "Arial,12" textcolor rgb "#222222" offset 0,0.6
set ylabel "Tempo Médio de Execução (Segundos - s)" font "Arial,12" textcolor rgb "#222222" offset 1.5,0

# Formatação do eixo Y (sem notação científica)
set format y "%.3f"

# Legenda estilizada
set key top left box lw 0.7 lc rgb "#AAAAAA" samplen 2 spacing 1.3 textcolor rgb "#222222"

# Cores profissionais e marcadores legíveis
set style line 1 lc rgb "#1f77b4" lw 2 pt 7 ps 1.1   # Azul
set style line 2 lc rgb "#ff7f0e" lw 2 pt 9 ps 1.1   # Laranja
set style line 3 lc rgb "#2ca02c" lw 2 pt 5 ps 1.1   # Verde
set style line 4 lc rgb "#d62728" lw 2 pt 13 ps 1.1  # Vermelho
set style line 5 lc rgb "#9467bd" lw 2 pt 11 ps 1.1  # Roxo
set style line 6 lc rgb "#8c564b" lw 2 pt 15 ps 1.1  # Marrom

# ==========================
# 1️⃣ Gráfico - Todos juntos
# ==========================
set title "Comparativo de Desempenho dos Algoritmos de Ordenação" font "Arial-Bold,13" textcolor rgb "#111111"
set output "grafico_todos.png"

plot \
    "resultados/resultadoBubble.txt"    using 1:($2/1e6) with linespoints ls 1 title "Bubble Sort", \
    "resultados/resultadoInsertion.txt" using 1:($2/1e6) with linespoints ls 2 title "Insertion Sort", \
    "resultados/resultadoSelection.txt" using 1:($2/1e6) with linespoints ls 3 title "Selection Sort", \
    "resultados/resultadoMerge.txt"     using 1:($2/1e6) with linespoints ls 4 title "Merge Sort", \
    "resultados/resultadoQuick.txt"     using 1:($2/1e6) with linespoints ls 5 title "Quick Sort", \
    "resultados/resultadoHeap.txt"      using 1:($2/1e6) with linespoints ls 6 title "Heap Sort"

# ==========================
# 2️⃣ Bubble x Insertion
# ==========================
set output "grafico_bubble_vs_insertion.png"
set title "Comparativo Bubble Sort × Insertion Sort" font "Arial-Bold,13"
plot \
    "resultados/resultadoBubble.txt"    using 1:($2/1e6) with linespoints ls 1 title "Bubble Sort", \
    "resultados/resultadoInsertion.txt" using 1:($2/1e6) with linespoints ls 2 title "Insertion Sort"

# ==========================
# 3️⃣ Selection x Heap
# ==========================
set output "grafico_selection_vs_heap.png"
set title "Comparativo Selection Sort × Heap Sort" font "Arial-Bold,13"
plot \
    "resultados/resultadoSelection.txt" using 1:($2/1e6) with linespoints ls 3 title "Selection Sort", \
    "resultados/resultadoHeap.txt"      using 1:($2/1e6) with linespoints ls 6 title "Heap Sort"

# ==========================
# 4️⃣ Merge x Quick
# ==========================
set output "grafico_merge_vs_quick.png"
set title "Comparativo Merge Sort × Quick Sort" font "Arial-Bold,13"
plot \
    "resultados/resultadoMerge.txt" using 1:($2/1e6) with linespoints ls 4 title "Merge Sort", \
    "resultados/resultadoQuick.txt" using 1:($2/1e6) with linespoints ls 5 title "Quick Sort"

