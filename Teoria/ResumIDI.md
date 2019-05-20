---
title: "ResumIDI"
author: Joan Bellavista 
geometry: margin=3cm
output: pdf_document
---
#Realisme

## Eliminació de Parts Amagades (EPA)
* Back Culling

![Back Culling](Images/BackCulling.png)

\pagebreak

## Il·luminació




* Models d'Iluminació Empírics o locals:
	Nomes consideren per el càlcul del color.

![ModelsEmpirics\label{ModelsEmpirics}](Images/ModelsEmpirics.png){width=200px}

* Models de traçat de raig:
	Consideren també objectes existents a l'escena (però només transmissions especulars)

![ModelsRaig\label{ModelsRaig}](Images/ModelsRaig.png){width=200px}

* Models de radiositat:
	Poden fer ombres i penombres però no miralls ni transparències. Són els més costosos.	

![ModelsRadiositat\label{ModelsRadiositat}](Images/ModelsRadiositat.png){width=200px}

\pagebreak

###Models Empírics (Locals)

+ Model Empíric Ambient

> > $I_{a\lambda}$: color de la llum ambient

> > $K_{a\lambda}$: coeficient de reflexió ambient 

> > $I_{\lambda}(P) = I_{f\lambda} K_{d\lambda}$

![Model Ambient](Images/ModelAmbient.png){width=200px}

+ Model Empíric difús (Lambert)

> > $I_{f\lambda}$: color de la llum de focus puntual

> > $K_{d\lambda}$: coeficient de reflexió difusa del material

> > $\cos(\phi):$ cosinus de l'angle entre la llum incident i la normal a la superfície del punt P


> > $I_{\lambda}(P) = I_{f\lambda} K_{d\lambda} \cos(\phi)$

> > > $si \hspace{0.2cm}  \phi < 90$

![Model Difús](Images/ModelDifus.png){width=200px}

\pagebreak

+ Model empíric especular (Phong)

> > $I_{f\lambda}$: color de la llum de focus puntual

> > $K_{s\lambda}$: coeficient de reflexió especular

> > n: exponent de reflexió especular

> > $I_{\lambda}(P) = I_{f\lambda} K_{s\lambda} cos^n(\alpha)$

> > > $si \hspace{0.2cm} \alpha < 90$

> La fórmula del color final és el sumatori dels tres models

![Model Especular](Images/ModelEspecular.png){width=200px}

#### Shading de polígons

+ Colorat Constant (Flat Shading): Color uniforme per tot el polígon (es calcula el color a un vèrtex). cada cara pot tenir diferent color. $C_{f} = C_{vertex}$

+ Colorat de Gouraud (Gouraud shading o Smooth shading): Es fa una interpolació entre els càlculs del color dels tres vèrtexs de cada triangle per cada fragment.  

### Suavitzat d'arestes

Normal per cara vs normal per vèrtex. (normal per vèrtex és més smooth)

\pagebreak

#Realitat virtual i Realitat aumentada

##Realitat virtual

Hi han tres aspectes que tenim en compte amb la relitat virtual:
> - La immersió (pot ser tàctil, visual...)

> - La Visualització

> - La interacció (normalment amb Haptic Devices)

+ Característiques de Immersió visual

> - Retinal disparity (La imatge d'un ull és diferent de la d'altre)

> - Fusion and stereopsis (El cervell és capaç de combinar les dos imatges i aconssegueix una única imatge amb profunditat)

> - Haptic Devices (Aparells que els usuaris de realitat virtual utilitzen per interectuar) 

+ Tipus de Sistemes de Realitat Virtual

> - Immersive (ulleres de realitat virtual)

> - Semi-Immersive (els dos ulls poden veure la pantalla (una única). Una de les tècniques utilitzades és ulleres polaritzades.)

+ Synthesis of stereo images

![Synthesis Stereo Images](Images/SynthesisStereoImages.png)

> - Càlcul de la camera stereo: 

> > - Posicio i orientació:

```
	lookAt (eye.x, eye.y, eye.z, target.x, target.y, target.z, up.x, up.y, up.z);
```

> > - Parametres intrínsics

```
	frustum (left, right, bottom, top, near ,far);	
```

> - Configuracions de sistemes VR

> > + Pantalla estàtica(projecció) + "head-tracking" (a partir de la posició del cap amb sensors a l'habitació) 

> > > * Els paràmatres a tenir en compte són: La posició dels ulls i la geometria de la pantalla 

> > + Pantall dinàmica (ulleres) + "head-tracking" 

> > > * Els paràmatres a tenir en compte són: (Orientació del cap i HMD frustum (paràmatres intrínsics de les ulleres)

> > > * Distorsió (Hi ha una distorsió que s'ha de contrarrestar)

+ Interacció

> - Selecció 3d 

> > * Hand extension techniques or 3D point cursors (mapeig de la mà del usuari)

> > * Ray-Based technique (Senyalar amb un làser *ray cursors*)

> - Navegació (Pot ser búsqueda o exploració)

## Realitat Augmentada

| Realitat Augmentada | Realitat Virtual | 
| ---------------- | ------------------- |
| L'usuari sap que està al món real | Els sentits estan sota el control del sistema | 
|||
| El sistema augmenta el món real | Totalment immersiu | 
> Necessitem un mecanisme per combinar el mon virtual i el real  

Hi han tres maneres de presentar visualment RA:

> + Video see-through (Ensenyem el món real i a sobre li posem el món virtual. Exemple: Smartphone).

> + Optical see-through: (Es veu el món real partir de transparències i es projecta la realitat virtual (a les ulleres)).

> + Projecció AR a objectes reals.

\pagebreak

#Disseny d'interaccions

## Fonaments bàsics d'interacció en UI

### Background (Teoria de la informació)

+ Teoria de la informació

![Teoria de la Informació](Images/InformationTheory.png)

\vspace{1cm}

+ Mesures d'informació: La incertesa (*uncertainty*) es mesurada per $\log_{2}(M)$.\linebreak Reescrivint la fórmula tenint en compte que la probabilitat $P = 1/M$:\linebreak $\log_{2}(M)= \log_{2}((\frac{1}{M})^{-1}) = \log_{2}(P^{-1}) = -\log_{2}(P)$

\vspace{0.2cm}

> La informació és la reducció de l'incertesa. Shannon Entropy mesura la quantitat d'informació: \hfill \linebreak $$H = \sum_{i=1}^{N}p_{i} \log_{2}\left(\frac{1}{p_{i}}\right) = -\sum_{i=1}^{N}p_{i} \log_{2} p_{i}$$

> > N és el nombre d'alternatives

> > $p_i$ és la probabilitat de la $i^{th}$

> > H és la quantitat d'informació esperada a rebre. (*no soroll*)

> Tot i la fórmula, no tota la informació arribarà al receptor. \linebreak Mitjana d'informació transmesa (R): \linebreak $$R = H_x - H_y(x)$$

> $H_y(x)$ és l'equivocació.

\pagebreak

### Hick-Hyman Law: Mesurant el Choice-Reaction time

+ Temps per prendre una decisió (*Reaction Time*)

$$RT = a + bH_T$$

> $a,b$ constants

> $H_T$ és la informació transmesa.

+ Llei de Hick-Hyman

$$H_T = \log_2(n+1)$$

> $n$ és el nombre de alternatives (equiprobables o no)

> La llei original no tenia el +1. El +1 és la incertesa de si respondre o no.

Per tant:

$$RT = a + b \log_2(n+1)$$

+ Evidencies de Hick-Hyman

> - La seva llei prediu acuradament en seleccions de menú a pantalla completa.

> - El temps de selecció decau logaritmicament amb la llargada del menú (però només si l'usuari ha apres la posició del ítem, en cas contrari, la relació és linial)

### La llei de Fitt: Measuring Pointing Time

Fitt diu que hi ha una relació linial entre el temps de moviment (*movement time MT*) i la dificultat de la tasca.

$$ MT = a + b ID $$

> $a$ nombre de vegades que comença/s'atua en segons

> $b$ velocitat inherent del dispositiu

\vspace{0.2cm}

+ Dificultat de la tasca

$$ ID = \log_2 \left(\frac{2A}{W}\right)$$

> $ID:$ Index de dificultat

> $A:$ Amplitut del moviment

> $W:$ Amplada del objectiu (*W = Width*)

![Amplitut i Amplada del objectiu](Images/AmplitudeWidthTarget.png)

\pagebreak

De la llei de Fitts s'han tret moltes variants:

+ Welford:

$$MT = a + b \log_2 \left(\frac{D+0.5W}{W}\right)$$

+ MacKenzie

$$MT = a + b \log_2 \left(\frac{D}{W}+1\right)$$

També s'han trobat extensions amb moviments 2D (no només 1D). Dos de les més acceptades són la de Crossman i la d'Accot.

\pagebreak

Aspectes com el cas que els objectius siguin molt petits o que el aparell sigui una pantalla tàctil, no estàn bén modelats per la llei de Fitts. Per això tenim **FFitts** (*Finger Fitts*), també anomenat PPMT (*Precision Pointing Movement Time*):

$$FFitts = a + b ID + d ID_2$$ 

$$FFitts = a + b \left[\log_2\left(\frac{cD}{W}\right)\right] + d \left[\log_2\left(\frac{e}{W}\right)\right]$$

> El primer factor logarítmic mesura el temps per moure el dit a la pantalla.

> El segon factor mesura el temps per posicionar el cursor.

> $D$ és la distància (mesurada en 3D), des de la posició inicial de la mà fins al primer contacte.

> Si la tasca consisteix en iterativament anar fent *click* a objectius: $D$ és la distància de un objectiu a un altre.

> $W$ és la mida del objectiu

> $a, b, c, d$, and $e$ són diferents per diferents casos.

### Crossing and Steering Laws: Continuos Gestures

![Crossing vs Pointing](Images/CrossVsPoint.png){ width=150px }


+ Configuracions de *crossing*

![Continuu vs Discret](Images/ContinuuvsDiscret.png){ width=250px }


![Ortogonal vs Collinear](Images/OrtogonalvsCollinear.png){ width=250px }

\pagebreak

+ Llei de *crossing*

$$ T = a + b \log_2 \left(\frac{D}{W}+1\right)$$

> $T$ és el temps mitjà de moure's passant per dos objectius.  

> $D$ és la distància entre dos objectius

> $W$ és la amplada de cada objectiu

> $a$ i $b$ són constants a determinar

+ Llei de *steering*

![Steering Law](Images/SteeringLaw.png){ width=250px}

Navegant per un camí generalitzat es pot expresar com infinits creuament (*crossing*)

Temps de moviment a través del camí $T_s$:

$$T_s = a + b ID_s$$	$$T_s = a + b \int_C \frac{ds}{W(s)}$$

> $C$ és la llargada del camí

> $W(s)$ és l'amplada del camí en el punt s

Amb la fórmula que tenim, calculem la fórmula per navegar en un camí recte(*túnel $T_p$*).

$$T_P = a + b \frac{D}{W}$$

> $D$ és la llargada del túnel

> $W$ és l'amplada del túnel

Si li apliquem el format de Fitt:

$$T_p = a + b ID_P$$	$$ID_P = \frac{D}{W}$$

\pagebreak

## La llei de Fitts en disseny d'interfícies d'usuari (*UI*)

### Aplicacions en disseny de UI

+ Corners

![Corners](Images/Corners.png){ width=250px }

> > La cantonada de la pantalla té infinites dimensiosn per tant és on més fàcil és arribar.

+ Mida Objectiu

![Mida Objectiu](Images/MidaObjectiu.png){width=250px}

> > Com més gran l'objectiu més senzilla la tasca.

+ Mantenir coses relacionades aprop.

+ Mantenir coses contràries lluny.

+ Menús *Pop-up*: Redeix la distància que s'ha de viatjar fins a arribar l'objectiu. 

\pagebreak

+ Menús "pastís" (*pie menus*): Ha d'aparèixer per demanda del usuari. No pot tenir oclusions (s'ha de poder veure tot).

![Pie Menu](Images/PieMenu.png){width=200px}

+ Percepció: Agrupar pot millorar més que tenir-ho aprop.

### Accelerant Target Acquisition

+ Augmentar la mida dels objectius quan el punter està més aprop.

![Augment per proximitat \label{Augment per proximitat}](Images/AugmentProximitat.png){width=250px}

+ *Bubble targets*

![BubbleTarget](Images/BubbleTarget.png){width=250px}

\pagebreak

+ *Bubble cursor*: La mida del cursor augmenta quan està aprop d'objectius. Creix segons la posició no velocitat.

![BubbleCursor](Images/BubbleCursor.png){width=250px}

+ *Dynamic Bubble cursor*: Té en compte la velocitat del mouse. La àrea del punter augmenta segons la posició i la velocitat.


![Dynamic Bubble Cursor](Images/DynamicBubbleCursor.png){width=250px}

+ Moure els objectius: Fent-los aparèixer al punter del usuari (*pop-up menus*) o apropant els objectius al usuari (veure Referencia \ref{Augment per proximitat}) 

+ *Sticky targets* (Atraure el punter quan està aprop d'una àrea seleccionalbe)

![Sticky Targets](Images/StickyTargets.png){width=250px}

\pagebreak

+ *Control-Display ratio*:  És la relació entre l'amplitud dels moviments de la mà del usuari i el cursor virtual. Hi han diverses estratègies.

> - Constant

> - Depenent de la velocitat del mouse (Ratolí en el cas de windows)

> - Depenent de la posició del cursor
