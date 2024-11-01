# RSSI-baserad positionering

Systemet använder received signal strength indicator (RSSI) från flera accesspunkter (APs) för att triangulera positionen. Denna triangulering bygger på att jämföra aktuella RSSI-värden med värden från en fingerprint databas med olika kända positioner $P$.

## K-Nearest Neighbor

Systemet använder algoritmen K-Nearest Neighbor (K-NN) där $K$ representerar antalet närmaste grannar som beaktas. Genom att jämföra uppmätta RSSI-värden identifieras $K$ för att beräkna den mest sannolika positionen.

Denna modell bygger på datapunkter där avståndet mäts med euklidiskt avstånd.

Enskilda punkter kan påverka klassificeringen. Litet K gör modellen känslig för brus. Stort K gör modellen mer stabil men beslutet blir mer generaliserat och mindre precist.

**Next position**
---

Programmet **Next position** uppskattar positionen vid nästa tidssteg $k$.

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

Förflyttning 20 längder nordost (45 grader), med start North 100, East 50
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

