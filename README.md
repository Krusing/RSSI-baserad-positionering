# RSSI-baserad positionering

Systemet använder received signal strength indicator (RSSI) från flera accesspunkter (APs) för att triangulera positionen. Denna triangulering bygger på att jämföra aktuella RSSI-värden med värden från en fingerprint databas med olika kända positioner $P$.

## K-Nearest Neighbor

Systemet använder algoritmen K-Nearest Neighbor (K-NN) där $K$ representerar antalet närmaste grannar som beaktas. Genom att jämföra uppmätta RSSI-värden identifieras $K$ för att beräkna den mest sannolika positionen.

Denna modell bygger på datapunkter där avståndet mäts med euklidiskt avstånd.

Enskilda punkter kan påverka klassificeringen. Litet K gör modellen känslig för brus. Stort K gör modellen mer stabil men beslutet blir mer generaliserat och mindre precist.

**Next position**
---

Programmet uppdaterar positionen vid nästa tidssteg $k$.

Vid varje tidssteg $k$ uppdaterar programmet den nuvarande positionen $\mathbf{x}_ {k}$ till en ny position $\mathbf{x}_ {k+1}$ baserat på rörelsens längd $L_k$ och riktning $\varphi_k$.

```math
\mathbf{x}_{k+1} = 
\begin{bmatrix} P_{k+1}^N \\ P_{k+1}^E \end{bmatrix} = 
\mathbf{x}_k + L_k 
\begin{bmatrix} \cos \varphi_k \\ \sin \varphi_k \end{bmatrix}
```

Så här kör du programmet

Källkod `./knn/next_p.c`

Kompilera koden
```
gcc -o next_p ./knn/next_p.c
```

**Testfall**

För att köra programmet med förflyttning 20 längder nordost (45 grader), med start North 100, East 50
```
./next_p 100 50 20 45
```
Förväntat output
```
114.14 64.14
```

## AP-signalstyrka matris

För $N$ APs visas $D$ med signalvärden $d_ 1, d_ 2, \dots, d_ M$ samt en identitetsmatris $I_ {L \times M}$. Programmet tar in argument som representerar signalstyrkor från flera accesspunkter, totalt 9 värden som indata.

```math
D = \begin{bmatrix}d_1&d_2&\dots&d_M&I_{L \times M} \end{bmatrix}
```

Så här kör du programmet

Källkod `./knn/ap_ss.c`

Kompilera koden

```
gcc -o ap_ss ./knn/ap_ss.c
```

**Testfall**

```
./ap_ss 1 2 3 4 5 6 7 8 9
```
Förväntat output
```
1.0 0.0 0.0
0.0 1.0 0.0
0.0 0.0 1.0

1.00 2.00 3.00
4.00 5.00 6.00
7.00 8.00 9.00
```

## APs RSSI-värden

Programmet hanterar RSSI-värden från flera APs och representerar dessa i en matris $r$.

```math
r = \begin{bmatrix}
r_{1,1}&r_{1,2}&\dots&r_{1,N}\\
r_{2,1}&r_{2,2}&\dots&M\\
M&M&O&M\\
r_{M,1}&r_{M,2}&\dots&r_{M,N}\end{bmatrix}
```

Så här kör du programmet

Källkod `./knn/ap_r.c`

Kompilera koden
```
gcc -o ap_r ./knn/ap_r.c
```

**Testfall**

För att köra programmet med 9 värden som RSSI-signalstyrkor från olika APs.
```
./ap_r 1 2 3 4 5 6 7 8 9
```
Förväntat output
```
1.00 2.00 3.00
4.00 5.00 6.00
7.00 8.00 9.00
```

## Fingerprint vektor

Programmet genererar en fingerprint vektor $d_ k$

```math
d_k \ (l) = 
\left[ \quad
\begin{array}{l}
\\
1 \quad r_{ki} < r_{kj} \\ \\
0 \quad r_{ki}^3 \, r_{kj} \\
\hspace{1em}
\end{array}
\begin{array}{l}
\hspace{1em} \\
& (i = 1, \dots, N, \, j = i+1, \dots, N) \\ \\
& k=1, \dots, M \quad 1 = (i-1)N - \frac{i(i+1)}{2}+j \\ \\
& (i = 1, \dots, N, j = i+1, \dots, N) \\
\hspace{1em}
\end{array}
\quad \right]
```
