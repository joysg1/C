#!/bin/bash

# Script para generar datos de prueba aleatorios
# 20 registros de empleados con datos variados

ARCHIVO_DATOS="empleados.txt"

# Arrays de datos para generar registros aleatorios
nombres=("Juan" "María" "Carlos" "Ana" "Luis" "Laura" "Pedro" "Isabel" "Ricardo" "Elena" 
         "Jorge" "Mónica" "Fernando" "Gabriela" "Diego" "Patricia" "Roberto" "Claudia" "Sergio" "Adriana")

apellidos=("Pérez" "García" "Rodríguez" "Martínez" "Hernández" "López" "González" "Díaz" 
           "Morales" "Castro" "Ruiz" "Vargas" "Silva" "Rojas" "Mendoza" "Guerrero" "Ortiz" 
           "Ramírez" "Flores" "Vega")

cargos=("Gerente" "Contador" "Desarrollador" "Diseñador" "Analista" "Recursos Humanos" 
        "Técnico" "Marketing" "Supervisor" "Soporte Técnico" "Asistente" "Ingeniero" 
        "Consultor" "Auditor" "Coordinador" "Especialista" "Investigador" "Administrador" 
        "Planificador" "Coordinador")

# Función para generar fecha aleatoria
generar_fecha() {
    local año=$((2020 + RANDOM % 4))  # 2020-2023
    local mes=$((1 + RANDOM % 12))
    local dia=$((1 + RANDOM % 28))
    printf "%04d-%02d-%02d" $año $mes $dia
}

# Función para generar salario base
generar_salario() {
    local salario=$((2500 + RANDOM % 2000))  # 25.00 - 45.00
    echo "scale=2; $salario / 100" | bc
}

# Función para generar horas trabajadas
generar_horas() {
    echo "scale=1; 30 + (RANDOM % 150) / 10" | bc  # 30.0 - 45.0
}

print_message() {
    echo -e "\033[0;32m[INFO]\033[0m $1"
}

print_step() {
    echo -e "\033[0;34m>>>\033[0m $1"
}

# Verificar si bc está instalado (para cálculos decimales)
if ! command -v bc &> /dev/null; then
    echo "Error: 'bc' no está instalado. Instálalo con: sudo apt-get install bc"
    exit 1
fi

# Verificar si el archivo ya existe
if [ -f "$ARCHIVO_DATOS" ]; then
    print_message "El archivo $ARCHIVO_DATOS ya existe"
    read -p "¿Desea sobrescribirlo? (y/n): " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        echo "Operación cancelada."
        exit 0
    fi
fi

print_step "Generando 20 registros aleatorios de empleados..."

# Crear archivo vacío
> "$ARCHIVO_DATOS"

# Generar 20 registros
for i in {1..20}; do
    id=$i
    nombre=${nombres[$((RANDOM % 20))]}
    apellido=${apellidos[$((RANDOM % 20))]}
    cargo=${cargos[$((RANDOM % 20))]}
    salario_base=$(generar_salario)
    horas_trabajadas=$(generar_horas)
    salario_neto=$(echo "scale=2; $salario_base * $horas_trabajadas" | bc)
    fecha_contratacion=$(generar_fecha)
    
    # Formatear el registro
    printf "%d,%s,%s,%s,%.2f,%.1f,%.2f,%s\n" \
        "$id" "$nombre" "$apellido" "$cargo" "$salario_base" "$horas_trabajadas" "$salario_neto" "$fecha_contratacion" >> "$ARCHIVO_DATOS"
    
    print_message "Registro $i generado: $nombre $apellido - $cargo"
done

print_message "Base de datos aleatoria creada exitosamente: $ARCHIVO_DATOS"
print_message "Total de registros generados: 20"

# Mostrar estadísticas
print_step "Estadísticas de la base de datos:"
echo ""
echo "📊 Resumen de datos generados:"
echo "   👥 Total empleados: 20"
echo "   💰 Rango salarial: \$25.00 - \$45.00 por hora"
echo "   ⏰ Horas trabajadas: 30.0 - 45.0 horas"
echo "   📅 Fechas de contratación: 2020-2023"
echo ""
echo "📋 Primeros 5 registros:"
head -n 5 "$ARCHIVO_DATOS"
echo ""
print_message "¡Base de datos aleatoria lista para usar!"
