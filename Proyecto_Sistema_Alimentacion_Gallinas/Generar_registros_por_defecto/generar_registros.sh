#!/bin/bash

# Script para generar base de datos COMPLETA (ambos archivos)
# Autor: Asistente

echo "🐔 GENERANDO BASE DE DATOS COMPLETA PARA SISTEMA DE GALLINAS"
echo "============================================================"

# Configuración
ARCHIVO_REGISTROS="base_datos_completa_registros.txt"
ARCHIVO_INVENTARIO="base_datos_completa_inventario.txt"
NUMERO_REGISTROS=100

# Arrays de datos (los mismos del script anterior)
alimentos=("Maíz molido" "Sorgo" "Harina de soya" "Salvado de trigo" "Conchuela" 
           "Premezcla vitaminas" "Aceite vegetal" "Pasta de algodón" "Harina de pescado"
           "Trigo" "Cebada" "Afrecho de arroz")

etapas=("polla" "desarrollo" "postura" "engorde")

proveedores=("Granos S.A." "Avícola Norte" "Proteínas Ltda." "Cereales del Valle" 
             "Minerales SAC" "NutriAvícola")

# Función simplificada para generar fecha
generar_fecha() {
    local mes=$((RANDOM % 5 + 1))  # 1-5 meses
    local dia=$((RANDOM % 28 + 1))
    echo "2024-0$mes-$(printf "%02d" $dia)"
}

# Crear archivo de REGISTROS
echo "Creando $NUMERO_REGISTROS registros de alimentación..."
echo "" > "$ARCHIVO_REGISTROS"

for i in $(seq 1 $NUMERO_REGISTROS); do
    fecha=$(generar_fecha)
    alimento=${alimentos[$((RANDOM % ${#alimentos[@]}))]}
    gallinas=$((RANDOM % 251 + 50))  # 50-300 gallinas
    
    # Cantidad según etapa
    etapa=${etapas[$((RANDOM % ${#etapas[@]}))]}
    case $etapa in
        "polla") cantidad=$(echo "scale=2; $gallinas * 0.06" | bc) ;;
        "desarrollo") cantidad=$(echo "scale=2; $gallinas * 0.08" | bc) ;;
        "postura") cantidad=$(echo "scale=2; $gallinas * 0.12" | bc) ;;
        "engorde") cantidad=$(echo "scale=2; $gallinas * 0.15" | bc) ;;
    esac
    
    proveedor=${proveedores[$((RANDOM % ${#proveedores[@]}))]}
    
    # Costo basado en alimento
    case $alimento in
        "Maíz molido") costo=$(echo "scale=2; $cantidad * 1.8" | bc) ;;
        "Harina de soya") costo=$(echo "scale=2; $cantidad * 3.2" | bc) ;;
        "Conchuela") costo=$(echo "scale=2; $cantidad * 3.5" | bc) ;;
        *) costo=$(echo "scale=2; $cantidad * 2.0" | bc) ;;
    esac
    
    observacion="Registro automático $i"
    
    echo "$fecha|$alimento|$cantidad|$gallinas|$etapa|$proveedor|$costo|$observacion" >> "$ARCHIVO_REGISTROS"
done

# Crear archivo de INVENTARIO
echo "Creando inventario de alimentos..."
cat > "$ARCHIVO_INVENTARIO" << EOF
Maíz molido|500.00|1.80|2024-01-15|2024-07-15
Harina de soya|200.00|3.20|2024-02-01|2024-08-01
Sorgo|300.00|1.60|2024-01-20|2024-07-20
Conchuela|50.00|3.50|2024-03-01|2024-09-01
Premezcla vitaminas|25.00|8.00|2024-02-15|2024-08-15
Salvado de trigo|150.00|1.20|2024-01-25|2024-07-25
Aceite vegetal|30.00|2.50|2024-02-10|2024-08-10
Harina de pescado|80.00|4.50|2024-03-05|2024-09-05
EOF

echo ""
echo "✅ BASE DE DATOS COMPLETA CREADA:"
echo "   📄 $ARCHIVO_REGISTROS - $NUMERO_REGISTROS registros de alimentación"
echo "   📄 $ARCHIVO_INVENTARIO - 8 productos en inventario"
echo ""
echo "🚀 PARA CARGAR AL SISTEMA:"
echo "   cp $ARCHIVO_REGISTROS registro_alimentacion.txt"
echo "   cp $ARCHIVO_INVENTARIO inventario_alimentos.txt"
echo ""
echo "🐓 O usar el sistema con: ./sistema_gallinas"
