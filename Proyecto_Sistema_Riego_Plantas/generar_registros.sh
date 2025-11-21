#!/bin/bash

# Script para crear base de datos de plantas ornamentales
# Esta base de datos puede cargarse automáticamente en el sistema

cat > registro_riego.txt << 'EOF'
Rosa|Arbusto ornamental|2024-01-15|2024-01-22|500|Riego profundo, evitar mojar flores
Suculenta Echeveria|Crasa|2024-01-14|2024-01-28|150|Riego escaso, sustrato bien drenado
Orquídea Phalaenopsis|Epífita|2024-01-13|2024-01-20|300|Riego por inmersión, agua sin cal
Helecho Nephrolepis|Fronde|2024-01-15|2024-01-18|400|Alta humedad ambiental, riego frecuente
Bambú de la Suerte|Hierba ornamental|2024-01-16|2024-01-23|250|Mantener raíces siempre húmedas
Cactus San Pedro|Cactácea|2024-01-10|2024-01-31|100|Riego mínimo, pleno sol
Lavanda|Aromática|2024-01-14|2024-01-21|350|Riego moderado, buen drenaje
Bonsái Ficus|Árbol miniatura|2024-01-15|2024-01-17|200|Riego por aspersión, humedad constante
Anturio|Tropical|2024-01-13|2024-01-19|400|Alta humedad, agua tibia
Poto|Trepadora|2024-01-16|2024-01-20|300|Riego regular, tolera sequía breve
Palma Areca|Palmera|2024-01-12|2024-01-19|600|Riego abundante, drenaje perfecto
Crotón|Follaje decorativo|2024-01-15|2024-01-18|350|Humedad constante sin encharcar
Jazmín|Trepadora floral|2024-01-14|2024-01-21|400|Riego regular, floración abundante
Aloe Vera|Medicinal|2024-01-10|2024-01-24|180|Riego escaso, sustrato arenoso
Hiedra|Trepadora|2024-01-16|2024-01-19|280|Riego moderado, soporta sombra
Buganvilla|Arbusto trepador|2024-01-13|2024-01-27|450|Riego escaso en invierno, abundante en verano
Cinta|Colgante|2024-01-15|2024-01-18|320|Riego regular, purifica aire
Gardenia|Arbusto floral|2024-01-14|2024-01-20|380|Agua sin cal, suelo ácido
Crisantemo|Anual|2024-01-16|2024-01-19|360|Riego frecuente durante floración
Azalea|Arbusto|2024-01-15|2024-01-18|420|Suelo ácido, agua sin cloro
Drácena|Arbusto|2024-01-12|2024-01-19|300|Riego moderado, tolera sequía
Espada de San Jorge|Suculenta|2024-01-10|2024-01-31|150|Riego muy escaso, indestructible
Petunia|Anual|2024-01-16|2024-01-19|400|Riego abundante en floración
Camelia|Arbusto|2024-01-13|2024-01-20|370|Agua sin cal, suelo húmedo
Geranio|Anual|2024-01-15|2024-01-18|350|Riego regular, pleno sol
Hortensia|Arbusto|2024-01-14|2024-01-18|500|Riego abundante, agua sin cal
Violeta Africana|Interior|2024-01-16|2024-01-19|200|Riego por abajo, evitar hojas
Bromelia|Tropical|2024-01-13|2024-01-20|250|Agua en el copete, alta humedad
Calathea|Follaje|2024-01-15|2024-01-18|350|Humedad constante, agua filtrada
Ficus Lyrata|Árbol interior|2024-01-12|2024-01-19|450|Riego moderado, hojas grandes
Monstera|Trepadora|2024-01-14|2024-01-21|400|Riego regular, soporta interior
Peperomia|Compacta|2024-01-16|2024-01-20|280|Riego moderado, buen drenaje
Cactus de Navidad|Cactácea|2024-01-13|2024-01-19|300|Riego regular durante crecimiento
Lirio de la Paz|Interior|2024-01-15|2024-01-18|380|Riego frecuente, purifica aire
Potus|Trepadora|2024-01-16|2024-01-20|320|Riego regular, muy resistente
Romero|Aromática|2024-01-14|2024-01-28|250|Riego escaso, pleno sol
Tomillo|Aromática|2024-01-13|2024-01-27|200|Riego mínimo, suelo seco
Menta|Aromática|2024-01-15|2024-01-18|450|Riego abundante, crece rápido
Albahaca|Aromática|2024-01-16|2024-01-19|400|Riego frecuente, evitar sequía
Cilantro|Aromática|2024-01-14|2024-01-18|380|Riego regular, suelo fresco
Jengibre|Aromática|2024-01-13|2024-01-20|350|Riego moderado, suelo húmedo
Cúrcuma|Aromática|2024-01-15|2024-01-19|360|Riego regular, clima cálido
Lirio|Bulbosa|2024-01-16|2024-01-20|420|Riego abundante durante crecimiento
Tulipán|Bulbosa|2024-01-14|2024-01-19|380|Riego moderado, floración primaveral
Narciso|Bulbosa|2024-01-13|2024-01-18|350|Riego regular, sol directo
Jacinto|Bulbosa|2024-01-15|2024-01-19|400|Riego abundante, floración fragante
Amaryllis|Bulbosa|2024-01-16|2024-01-20|450|Riego moderado, floración espectacular
Gladiolo|Bulbosa|2024-01-14|2024-01-19|420|Riego regular, tallos largos
Dalias|Bulbosa|2024-01-13|2024-01-18|480|Riego abundante, flores grandes
Begonia|Anual|2024-01-15|2024-01-19|350|Riego moderado, evitar exceso
Coleo|Follaje|2024-01-16|2024-01-20|320|Riego regular, colores vibrantes
Impatiens|Anual|2024-01-14|2024-01-18|400|Riego frecuente, sombra parcial
Vinca|Anual|2024-01-13|2024-01-19|380|Riego moderado, resistente
Zinnia|Anual|2024-01-15|2024-01-18|350|Riego regular, atraen mariposas
Girasol|Anual|2024-01-16|2024-01-19|500|Riego abundante, crecimiento rápido
Margarita|Perenne|2024-01-14|2024-01-21|400|Riego regular, floración continua
Clavel|Perenne|2024-01-13|2024-01-19|380|Riego moderado, flores fragantes
Lavanda|Perenne|2024-01-15|2024-01-28|300|Riego escaso, aroma relajante
Salvia|Perenne|2024-01-16|2024-01-23|350|Riego moderado, atrae polinizadores
Rudbeckia|Perenne|2024-01-14|2024-01-21|420|Riego regular, floración otoñal
Echinacea|Perenne|2024-01-13|2024-01-20|380|Riego moderado, medicinal
Sedum|Suculenta|2024-01-15|2024-01-29|200|Riego escaso, muy resistente
AEonium|Suculenta|2024-01-16|2024-01-30|180|Riego mínimo, forma roseta
Crassula|Suculenta|2024-01-14|2024-01-28|220|Riego escaso, árbol de jade
Kalanchoe|Suculenta|2024-01-13|2024-01-27|250|Riego moderado, floración prolongada
Haworthia|Suculenta|2024-01-15|2024-01-29|150|Riego muy escaso, crecimiento lento
Senecio|Suculenta|2024-01-16|2024-01-30|200|Riego mínimo, forma colgante
Lithops|Suculenta|2024-01-10|2024-02-10|50|Riego casi nulo, piedras vivas
Agracejo|Arbusto|2024-01-14|2024-01-28|400|Riego moderado, seto decorativo
Boj|Arbusto|2024-01-13|2024-01-27|380|Riego regular, poda topiaria
Adelfa|Arbusto|2024-01-15|2024-01-29|450|Riego moderado, tóxica pero hermosa
Hibisco|Arbusto|2024-01-16|2024-01-22|500|Riego abundante, flores grandes
Lilo|Arbusto|2024-01-14|2024-01-21|480|Riego regular, aroma intenso
Forsitia|Arbusto|2024-01-13|2024-01-20|420|Riego moderado, floración temprana
Weigela|Arbusto|2024-01-15|2024-01-22|400|Riego regular, atrae colibríes
Spirea|Arbusto|2024-01-16|2024-01-23|380|Riego moderado, crecimiento rápido
Nandina|Arbusto|2024-01-14|2024-01-28|350|Riego escaso, follaje colorido
Durillo|Arbusto|2024-01-13|2024-01-27|400|Riego moderado, muy resistente
Laurel|Arbusto|2024-01-15|2024-01-29|450|Riego regular, aromático
Mirto|Arbusto|2024-01-16|2024-01-23|420|Riego moderado, floración estival
Madreselva|Trepadora|2024-01-14|2024-01-21|500|Riego abundante, aroma nocturno
Glicinia|Trepadora|2024-01-13|2024-01-27|600|Riego regular, crecimiento vigoroso
Jazmín Estrella|Trepadora|2024-01-15|2024-01-22|450|Riego moderado, floración blanca
Pasiflora|Trepadora|2024-01-16|2024-01-23|480|Riego regular, flores exóticas
Clemátide|Trepadora|2024-01-14|2024-01-21|420|Riego moderado, base sombreada
Hiedra|Trepadora|2024-01-13|2024-01-20|350|Riego regular, cubresuelos
Parra Virgen|Trepadora|2024-01-15|2024-01-29|500|Riego moderado, color otoñal
Trébol|Cubresuelos|2024-01-16|2024-01-19|300|Riego frecuente, crecimiento rápido
Verdolaga|Cubresuelos|2024-01-14|2024-01-28|250|Riego escaso, muy resistente
Gazania|Cubresuelos|2024-01-13|2024-01-27|350|Riego moderado, flores coloridas
Portulaca|Cubresuelos|2024-01-15|2024-01-29|300|Riego escaso, tolera sequía
Lamiun|Cubresuelos|2024-01-16|2024-01-20|400|Riego regular, follaje plateado
Ajuga|Cubresuelos|2024-01-14|2024-01-21|380|Riego moderado, crecimiento denso
Pensamiento|Anual|2024-01-13|2024-01-18|350|Riego frecuente, floración invernal
Ciclamen|Anual|2024-01-15|2024-01-19|320|Riego por abajo, temperatura fresca
Primula|Anual|2024-01-16|2024-01-20|380|Riego regular, colores vibrantes
Caléndula|Anual|2024-01-14|2024-01-21|400|Riego moderado, medicinal
Tagete|Anual|2024-01-13|2024-01-19|350|Riego regular, repele plagas
Ageratum|Anual|2024-01-15|2024-01-20|320|Riego frecuente, flores azules
EOF

echo "✅ Base de datos creada con 100 plantas ornamentales!"
echo "📊 Total de registros: $(wc -l < registro_riego.txt)"
