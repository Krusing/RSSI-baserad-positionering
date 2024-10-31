## RSSI-baserad positionering

Systemet använder received signal strength indicator (RSSI) från flera accesspunkter (APs) för att triangulera positionen. Denna triangulering bygger på att jämföra aktuella RSSI-värden med värden från en fingerprint databas med olika kända positioner $P$.

### K-Nearest Neighbor

Systemet använder algoritmen K-Nearest Neighbor (K-NN) där $K$ representerar antalet närmaste grannar som beaktas. Genom att jämföra uppmätta RSSI-värden identifieras $K$ för att beräkna den mest sannolika positionen.

Denna modell bygger på datapunkter där avståndet mäts med euklidiskt avstånd.

Enskilda punkter kan påverka klassificeringen. Litet K gör modellen känslig för brus. Stort K gör modellen mer stabil men beslutet blir mer generaliserat och mindre precist.

### K-NN algoritmen

Programmet **Next position** uppskattar positionen vid nästa tidssteg $k$.

`./knn/next_p.c`

Vid varje tidssteg $k$ uppdaterar programmet den nuvarande positionen $\mathbf{x}_ {k}$ till en ny position $\mathbf{x}_ {k+1}$ baserat på rörelsens längd $L_k$ och riktning $\varphi_k$ enligt formeln

```math
\mathbf{x}_{k+1} = 
\begin{bmatrix} P_{k+1}^N \\ P_{k+1}^E \end{bmatrix} = 
\mathbf{x}_k + L_k 
\begin{bmatrix} \cos \varphi_k \\ \sin \varphi_k \end{bmatrix}
```
