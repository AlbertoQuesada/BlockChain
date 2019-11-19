/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.artelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   B L A N K   A P P L I C A T I O N                                                                          */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// System includes

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <time.h>
#include <algorithm>

#include <stdint.h>
#include <limits.h>

#include<QString.h>
#include<QFile.h>
#include<QTextStream.h>
#include<QTextCodec.h>
#include<QVector.h>
#include<QDebug.h>

// OpenNN includes

#include "../opennn/opennn.h"

using namespace OpenNN;

std::string original_data_filename = "C:/Users/Roberto/Desktop/mc_donalds_chile/data/aaa.csv";
std::string clean_data_filename = "C:/Users/Roberto/Desktop/mc_donalds_chile/data/mc_donalds_chile_clean.csv";
std::string nn_data_filename = "C:/Users/Roberto/Desktop/mc_donalds_chile/data/mc_donalds_chile_nn.csv";

void data_preparation(void)
{
    Matrix<std::string> data;

    std::cout << "Load" << std::endl;

    data.load_strings(original_data_filename, ',');

    std::cout << "Replace elements" << std::endl;

    data.replace("undefined", "NA");
    data.replace("null", "NA");
    data.replace("false", "0");
    data.replace("true", "1");
    data.replace("m", "male");

    data.replace("male", "1");
    data.replace("female", "0");

    data.replace_contains("ANDROID_", "ANDROID");
    data.replace_contains("IOS_", "IOS");

    data.replace_substring(" GMT+0000 (UTC)", "");

    std::cout << "Subtract columns" << std::endl;

    data.subtract_column_by_name("campaignId");
    data.subtract_column_by_name("updateAt");
    data.subtract_column_by_name("downloadAt");
    data.subtract_column_by_name("clientName");
    data.subtract_column_by_name("clientEmail");
    data.subtract_column_by_name("osVersion");
    data.subtract_column_by_name("handSet");
    data.subtract_column_by_name("code");

    std::cout << "Convert time columns" << std::endl;

    data.convert_time_column("createdAt");
    data.convert_time_column("deliveredAt");
    data.convert_time_column("redeemAt");

    std::cout << "Split columns" << std::endl;

//        Vector<std::string> creation_names(5);
//        creation_names[0] = "creation_weekday";
//        creation_names[1] = "creation_month";
//        creation_names[2] = "creation_month_day";
//        creation_names[3] = "creation_year";
//        creation_names[4] = "creation_time";
//        data.split_column("createdAt", creation_names, ' ', "NA");
//        data.subtract_column_by_name("creation_year");

//        Vector<std::string> delivery_names(5);
//        delivery_names[0] = "delivery_weekday";
//        delivery_names[1] = "delivery_month";
//        delivery_names[2] = "delivery_month_day";
//        delivery_names[3] = "delivery_year";
//        delivery_names[4] = "delivery_time";
//        data.split_column("deliveredAt", delivery_names, ' ', "NA");
//        data.subtract_column_by_name("delivery_year");

//        Vector<std::string> redemption_names(5);
//        redemption_names[0] = "redemption_weekday";
//        redemption_names[1] = "redemption_month";
//        redemption_names[2] = "redemption_month_day";
//        redemption_names[3] = "redemption_year";
//        redemption_names[4] = "redemption_time";
//        data.split_column("redeemAt", redemption_names, ' ', "NA");
//        data.subtract_column_by_name("redemption_year");

//        Vector<std::string> download_names(5);
//        download_names[0] = "download_weekday";
//        download_names[1] = "download_month";
//        download_names[2] = "download_month_day";
//        download_names[3] = "download_year";
//        download_names[4] = "download_time";
//        data.split_column("downloadAt", download_names, ' ', "NA");
//        data.subtract_column_by_name("download_year");

    Vector<std::string> birth_names(5);
    birth_names[0] = "birth_weekday";
    birth_names[1] = "birth_month";
    birth_names[2] = "birth_month_day";
    birth_names[3] = "birth_year";
    birth_names[4] = "birth_time";
    data.split_column("clientBirthDate", birth_names, ' ', "NA");
    data.subtract_column_by_name("birth_weekday");
    data.subtract_column_by_name("birth_month");
    data.subtract_column_by_name("birth_month_day");
    data.subtract_column_by_name("birth_weekday");
    data.subtract_column_by_name("birth_time");

    std::cout << "Replace" << std::endl;

//        data.replace("Mon", "1");
//        data.replace("Tue", "2");
//        data.replace("Wed", "3");
//        data.replace("Thu", "4");
//        data.replace("Fri", "5");
//        data.replace("Sat", "6");
//        data.replace("Sun", "7");

//        data.replace("Jan", "1");
//        data.replace("Feb", "2");
//        data.replace("Mar", "3");
//        data.replace("Apr", "4");
//        data.replace("May", "5");
//        data.replace("Jun", "6");
//        data.replace("Jul", "7");
//        data.replace("Aug", "8");
//        data.replace("Sep", "9");
//        data.replace("Oct", "10");
//        data.replace("Nov", "11");
//        data.replace("Dec", "12");

    data.replace_contains("2 Milkshake por $3.490", "2 Milkshake por $3.490 - todos los dias en McCafe");
    data.replace_contains("2 Combos Nuggets de 10 por $4.490", "2 Combos Nuggets de 10 por $4.490 - todos los dias");
    data.replace_contains("2 Combos McPollo Italiano por $4.490", "2 Combos McPollo Italiano por $4.490 - todos los dias");
    data.replace_contains("Cafe 9oz mas Marraqueta Jamon-Queso por $1.290", "Cafe 9oz mas Marraqueta Jamon-Queso por $1.290 - todos los dias");
    data.replace_contains("Cafe 9oz mas Marraqueta Jamon-Queso por $1.290", "Cafe 9oz mas Marraqueta Jamon-Queso por $1.290 - todos los dias");
    data.replace_contains("2 Hamburguesas Queso mas Papa y Bebida", "2 Hamburguesas Queso mas Papa y Bebida Pequena por $2.290");
    data.replace_contains("2 Hamburguesas Queso mas Bebida", "2 Hamburguesas Queso mas Bebida Pequena por $1.990");
    data.replace_contains("Capuccino", "Capuccino Tentacion + Muffin por $2.990.- solo en McCafe");
    data.replace_contains("Marraqueta Jamon Queso por $1.290", "Cafe 9oz mas Marraqueta Jamon Queso por $1.290.- todos los dias");
    data.replace_contains("Marraqueta Jamon Queso + 2 Medialunas por $2.590", "Cafe Latte mas Marraqueta Jamon Queso + 2 Medialunas por $2.590");
    data.replace_contains("empanada por $ 4.990", "McCombo Doble 1/4 de Libra mas porcion de empanada por $ 4.990");
    data.replace_contains("Triple Hamburguesa Queso", "Triple Hamburguesa Queso mas Bebida Mediana por $1.990.- de lunes a viernes");
    data.replace_contains("le regalamos una Papa Frita Grande - Chile", "En el dia Del Padre le regalamos una Papa Frita Grande - Chile");
    data.replace_contains("2 Frappe por $ 3.990", "2 Frappe por $ 3.990.- Solo en McCafe");
    data.replace_contains("Combo Familiar por $9.590.", "Combo Familiar por $9.590");
    data.replace_contains("Cuarto de Libra a $1.000.- entre las 15:00 y 19:00 horas", "CUARTO DE LIBRA A $1.000.- entre las 15:00 y 19:00 horas");
    data.replace("2 Papas Medianas por $1.300.", "2 Papas Medianas por $1.300");
    data.replace("2 Cono Oreo por $800.", "2 Cono Oreo por $800");
    data.replace("2 Cono Oreo por $800. ", "2 Cono Oreo por $800");
    data.replace("2 Cuarto de Libra mas Bebida Mediana por $4.700.- Viernes y Sabado entre las 24:00 -04:00 h", "2 Cuarto de Libra mas Bebida Mediana por $4.700.- Viernes y Sabado entre las 24:00 -04:00 horas");
    data.replace("2 Cuarto de Libra mas Bebida Mediana por $4.700.- Viernes y Sabado entre las 24:00 -04:00 hrs", "2 Cuarto de Libra mas Bebida Mediana por $4.700.- Viernes y Sabado entre las 24:00 -04:00 horas");
    data.replace("2 Cuarto de Libra mas Bebida Mediana por $4.700.- Viernes y Sabado entre las 24:00 -04:00 hrs", "2 Cuarto de Libra mas Bebida Mediana por $4.700.- Viernes y Sabado entre las 24:00 -04:00 horas");

//        data.replace_contains("00:", "00");
//        data.replace_contains("01:", "01");
//        data.replace_contains("02:", "02");
//        data.replace_contains("03:", "03");
//        data.replace_contains("04:", "04");
//        data.replace_contains("05:", "05");
//        data.replace_contains("06:", "06");
//        data.replace_contains("07:", "07");
//        data.replace_contains("08:", "08");
//        data.replace_contains("09:", "09");
//        data.replace_contains("10:", "10");
//        data.replace_contains("11:", "11");
//        data.replace_contains("12:", "12");
//        data.replace_contains("13:", "13");
//        data.replace_contains("14:", "14");
//        data.replace_contains("15:", "15");
//        data.replace_contains("16:", "16");
//        data.replace_contains("17:", "17");
//        data.replace_contains("18:", "18");
//        data.replace_contains("19:", "19");
//        data.replace_contains("20:", "20");
//        data.replace_contains("21:", "21");
//        data.replace_contains("22:", "22");
//        data.replace_contains("23:", "23");

    std::cout << "Save" << std::endl;

    data.save_csv(clean_data_filename);
}


void data_preparation_neural_designer(void)
{
    std::cout << std::endl
              << "Data preparation for Neural Designer: " << std::endl;

    std::cout << "Load data" << std::endl;

    Matrix<std::string> data;
    data.load_strings(original_data_filename, ',');

    std::cout << "Replace elements" << std::endl;

    data.replace("undefined", "NA");
    data.replace("null", "NA");
    data.replace("false", "0");
    data.replace("true", "1");
    data.replace("m", "male");

    data.replace("male", "1");
    data.replace("female", "0");

    data.replace_contains("ANDROID_", "ANDROID");
    data.replace_contains("IOS_", "IOS");

    data.replace_substring(" GMT+0000 (UTC)", "");

    std::cout << "Subtract columns" << std::endl;

    data.subtract_column_by_name("clientId");
    data.subtract_column_by_name("clientIdBackup");
    data.subtract_column_by_name("clientCountry");
    data.subtract_column_by_name("clientGenre");
    data.subtract_column_by_name("couponId");
    data.subtract_column_by_name("campaignId");
    data.subtract_column_by_name("createdAt");
    data.subtract_column_by_name("updateAt");
    data.subtract_column_by_name("downloadAt");
    data.subtract_column_by_name("clientName");
    data.subtract_column_by_name("clientEmail");
    data.subtract_column_by_name("osVersion");
    data.subtract_column_by_name("handSet");
    data.subtract_column_by_name("code");

    std::cout << "Split columns" << std::endl;

    Vector<std::string> delivery_names(5);
    delivery_names[0] = "delivery_weekday";
    delivery_names[1] = "delivery_month";
    delivery_names[2] = "delivery_month_day";
    delivery_names[3] = "delivery_year";
    delivery_names[4] = "delivery_time";
    data.split_column("deliveredAt", delivery_names, ' ', "NA");
    data.subtract_column_by_name("delivery_month");
    data.subtract_column_by_name("delivery_year");

    data.replace_column_equal_to("redeemAt", "NA", "0", true);
    data.replace_column_not_equal_to("redeemAt", "NA", "1", true);

    Vector<std::string> birth_names(5);
    birth_names[0] = "birth_weekday";
    birth_names[1] = "birth_month";
    birth_names[2] = "birth_month_day";
    birth_names[3] = "birth_year";
    birth_names[4] = "birth_time";
    data.split_column("clientBirthDate", birth_names, ' ', "NA");
    data.subtract_column_by_name("birth_weekday");
    data.subtract_column_by_name("birth_month");
    data.subtract_column_by_name("birth_month_day");
    data.subtract_column_by_name("birth_weekday");
    data.subtract_column_by_name("birth_time");

    std::cout << "Replace" << std::endl;

    data.replace_column_contains("delivery_weekday", "Mon", "1", true);
    data.replace_column_contains("delivery_weekday", "Tue", "2", true);
    data.replace_column_contains("delivery_weekday", "Wed", "3", true);
    data.replace_column_contains("delivery_weekday", "Thu", "4", true);
    data.replace_column_contains("delivery_weekday", "Fri", "5", true);
    data.replace_column_contains("delivery_weekday", "Sat", "6", true);
    data.replace_column_contains("delivery_weekday", "Sun", "7", true);

    data.replace_column_contains("delivery_time", "00:", "00", true);
    data.replace_column_contains("delivery_time", "01:", "01", true);
    data.replace_column_contains("delivery_time", "02:", "02", true);
    data.replace_column_contains("delivery_time", "03:", "03", true);
    data.replace_column_contains("delivery_time", "04:", "04", true);
    data.replace_column_contains("delivery_time", "05:", "05", true);
    data.replace_column_contains("delivery_time", "06:", "06", true);
    data.replace_column_contains("delivery_time", "07:", "07", true);
    data.replace_column_contains("delivery_time", "08:", "08", true);
    data.replace_column_contains("delivery_time", "09:", "09", true);
    data.replace_column_contains("delivery_time", "10:", "10", true);
    data.replace_column_contains("delivery_time", "11:", "11", true);
    data.replace_column_contains("delivery_time", "12:", "12", true);
    data.replace_column_contains("delivery_time", "13:", "13", true);
    data.replace_column_contains("delivery_time", "14:", "14", true);
    data.replace_column_contains("delivery_time", "15:", "15", true);
    data.replace_column_contains("delivery_time", "16:", "16", true);
    data.replace_column_contains("delivery_time", "17:", "17", true);
    data.replace_column_contains("delivery_time", "18:", "18", true);
    data.replace_column_contains("delivery_time", "19:", "19", true);
    data.replace_column_contains("delivery_time", "20:", "20", true);
    data.replace_column_contains("delivery_time", "21:", "21", true);
    data.replace_column_contains("delivery_time", "22:", "22", true);
    data.replace_column_contains("delivery_time", "23:", "23", true);


    data.replace_contains("2 Milkshake por $3.490", "2 Milkshake por $3.490 - todos los dias en McCafe");
    data.replace_contains("2 Combos Nuggets de 10 por $4.490", "2 Combos Nuggets de 10 por $4.490 - todos los dias");
    data.replace_contains("2 Combos McPollo Italiano por $4.490", "2 Combos McPollo Italiano por $4.490 - todos los dias");
    data.replace_contains("Cafe 9oz mas Marraqueta Jamon-Queso por $1.290", "Cafe 9oz mas Marraqueta Jamon-Queso por $1.290 - todos los dias");
    data.replace_contains("Cafe 9oz mas Marraqueta Jamon-Queso por $1.290", "Cafe 9oz mas Marraqueta Jamon-Queso por $1.290 - todos los dias");
    data.replace_contains("2 Hamburguesas Queso mas Papa y Bebida", "2 Hamburguesas Queso mas Papa y Bebida Pequena por $2.290");
    data.replace_contains("2 Hamburguesas Queso mas Bebida", "2 Hamburguesas Queso mas Bebida Pequena por $1.990");
    data.replace_contains("Capuccino", "Capuccino Tentacion + Muffin por $2.990.- solo en McCafe");
    data.replace_contains("Marraqueta Jamon Queso por $1.290", "Cafe 9oz mas Marraqueta Jamon Queso por $1.290.- todos los dias");
    data.replace_contains("Marraqueta Jamon Queso + 2 Medialunas por $2.590", "Cafe Latte mas Marraqueta Jamon Queso + 2 Medialunas por $2.590");
    data.replace_contains("empanada por $ 4.990", "McCombo Doble 1/4 de Libra mas porcion de empanada por $ 4.990");
    data.replace_contains("Triple Hamburguesa Queso", "Triple Hamburguesa Queso mas Bebida Mediana por $1.990.- de lunes a viernes");
    data.replace_contains("le regalamos una Papa Frita Grande - Chile", "En el dia Del Padre le regalamos una Papa Frita Grande - Chile");
    data.replace_contains("2 Frappe por $ 3.990", "2 Frappe por $ 3.990.- Solo en McCafe");
    data.replace_contains("Combo Familiar por $9.590.", "Combo Familiar por $9.590");
    data.replace_contains("Cuarto de Libra a $1.000.- entre las 15:00 y 19:00 horas", "CUARTO DE LIBRA A $1.000.- entre las 15:00 y 19:00 horas");
    data.replace("2 Papas Medianas por $1.300.", "2 Papas Medianas por $1.300");
    data.replace("2 Cono Oreo por $800.", "2 Cono Oreo por $800");
    data.replace("2 Cono Oreo por $800. ", "2 Cono Oreo por $800");
    data.replace("2 Cuarto de Libra mas Bebida Mediana por $4.700.- Viernes y Sabado entre las 24:00 -04:00 h", "2 Cuarto de Libra mas Bebida Mediana por $4.700.- Viernes y Sabado entre las 24:00 -04:00 horas");
    data.replace("2 Cuarto de Libra mas Bebida Mediana por $4.700.- Viernes y Sabado entre las 24:00 -04:00 hrs", "2 Cuarto de Libra mas Bebida Mediana por $4.700.- Viernes y Sabado entre las 24:00 -04:00 horas");
    data.replace("2 Cuarto de Libra mas Bebida Mediana por $4.700.- Viernes y Sabado entre las 24:00 -04:00 hrs", "2 Cuarto de Libra mas Bebida Mediana por $4.700.- Viernes y Sabado entre las 24:00 -04:00 horas");

    std::cout << "Save" << std::endl;

    data.save_csv(nn_data_filename);
}


void integrity_analysis(void)
{
        std::cout << "Integrity analysis: " << std::endl;

        Matrix<std::string> data;
        data.load_strings(clean_data_filename, ',');

        const size_t rows_number = data.get_rows_number();
        const size_t columns_number = data.get_columns_number();

        std::cout << "Coupons number: " << rows_number - 1 << std::endl;
        std::cout << "Features number: " << columns_number << std::endl;

//        for(size_t i = 0; i < columns_number; i++)
//        {
//            std::cout << data(0,i) << ": " << data.arrange_column(i).count_equal_to("NA")*100/(rows_number-1.0) << "%" << std::endl;
//        }

    // Unique elements

//        std::cout <<  std::endl
//                  << "Unique elements: " << std::endl;

//        for(size_t i = 0; i < columns_number; i++)
//        {
//            std::cout << i << " " << data(0,i) << ": " << data.arrange_column(i).arrange_unique().size() - 1 << std::endl;
//        }

}


void performance_analysis(void)
{
    std::cout << "Performance analysis" << std::endl;

    Matrix<std::string> data;
    data.load_strings(clean_data_filename, ',');

    const Matrix<std::string> redemption_data = data.filter_column_not_equal_to("redeemAt", "NA");
    const size_t redemed_coupons = redemption_data.get_rows_number()-1;
    const double redemed_percentage = redemed_coupons;

//    std::cout << "Redemed coupons: " << redemed_coupons << " (" << redemed_percentage << "% of delivered)" << std::endl;

    const Vector<int> redemption = redemption_data.arrange_column("redeemAt").remove_element(0).string_to_int();

    const size_t redemption_size = redemption.size();

    Vector<int> redemption_month(redemption_size);
    Vector<int> redemption_day(redemption_size);
    Vector<int> redemption_weekday(redemption_size);
    Vector<int> redemption_hour(redemption_size);

    time_t time;
    struct tm* time_info;

    for(size_t i = 0; i < redemption_size-1; i++)
    {
        time = redemption[i];

        time_info = gmtime(&time);

        redemption_month[i] = time_info->tm_mon + 1;
        redemption_day[i] = time_info->tm_mday;
        redemption_weekday[i] = time_info->tm_wday;
        redemption_hour[i] = time_info->tm_hour;
    }

    // Month

//    std::cout << redemption_month.arrange_unique() << std::endl;
//    std::cout << std::endl;
//    std::cout << redemption_month.count_unique() << std::endl;

    // Day

    std::cout << redemption_day.arrange_unique() << std::endl;
    std::cout << std::endl;
    std::cout << redemption_day.count_unique() << std::endl;

    // Weekday

//    std::cout << redemption_weekday.arrange_unique() << std::endl;
//    std::cout << std::endl;
//    std::cout << redemption_weekday.count_unique() << std::endl;

    // Hour

    std::cout << redemption_hour.arrange_unique() << std::endl;
    std::cout << std::endl;
    std::cout << redemption_hour.count_unique() << std::endl;

}


void customer_analysis(void)
{
        std::cout << "Customer analysis: " << std::endl;


    Matrix<std::string> data;
    data.load_strings(clean_data_filename, ',');

//        const size_t created_coupons = data.get_rows_number()-1;

//        std::cout << "Created coupons: " << created_coupons << std::endl;

//        const Vector<std::string> creation_unique_names = data.arrange_column(0).arrange_unique();
//        const Vector<size_t> creation_unique_count = data.arrange_column(0).count_unique();

//        std::cout << std::endl;
//        std::cout << creation_unique_names << std::endl;
//        std::cout << std::endl;
//        std::cout << creation_unique_count << std::endl;
//        std::cout << std::endl;

//        std::cout <<  std::endl
//                  << "Delivery: " << std::endl;

//        const Matrix<std::string> delivery_data = data.filter_column_not_equal_to("delivery_weekday", "NA");

//        const size_t delivered_coupons = delivery_data.get_rows_number()-1;

//        const double delivered_percentage = 100.0*(double)delivered_coupons/(double)created_coupons;

//        std::cout << "Delivered coupons: " << delivered_coupons << " (" << delivered_percentage << "% of created)" << std::endl;

//        const Vector<std::string> delivery_unique_names = delivery_data.arrange_column(0).arrange_unique();
//        const Vector<size_t> delivery_unique_count = delivery_data.arrange_column(0).count_unique();

//        std::cout << std::endl;
//        std::cout << delivery_unique_names << std::endl;
//        std::cout << std::endl;
//        std::cout << delivery_unique_count << std::endl;
//        std::cout << std::endl;

//        std::cout <<  std::endl
//                  << "Redemption: " << std::endl;

//        const Matrix<std::string> redemption_data = data.filter_column_not_equal_to("redemption_weekday", "NA");

//        const double redemed_percentage = 100.0*(double)redemed_coupons/(double)delivered_coupons;

//        std::cout << "Redemed coupons: " << redemed_coupons << " (" << redemed_percentage << "% of delivered)" << std::endl;

//        const Vector<std::string> redemption_unique_names = redemption_data.arrange_column(0).arrange_unique();
//        const Vector<size_t> redemption_unique_count = redemption_data.arrange_column(0).count_unique();

//        std::cout << std::endl;
//        std::cout << redemption_unique_names << std::endl;
//        std::cout << std::endl;
//        std::cout << redemption_unique_count << std::endl;
//        std::cout << std::endl;

//        std::cout <<  std::endl
//                  << "Gender segmentation: " << std::endl;

//        const Vector<double> client_genre = redemption_data.arrange_column("clientGenre").string_to_double();

//        const size_t segment_male = redemption_data.count_equal_to("clientGenre", "male");
//        const size_t segment_female = redemption_data.count_equal_to("clientGenre", "female");

//        const size_t total_genre = segment_male+segment_female;

//        std::cout << "segment_male: " << segment_male << "(" << 100.0*(double)segment_male/(double)total_genre << ")%" << std::endl;
//        std::cout << "segment_female: " << segment_female << "(" << 100.0*(double)segment_female/(double)total_genre << ")%" << std::endl;

    // Age segmentation

//        std::cout <<  std::endl
//                  << "Age segmentation: " << std::endl;

//        const Vector<int> birth_year = redemption_data.arrange_column("birth_year").string_to_int();

//        const Vector<int> this_year(redemed_coupons, 2017);

//        Vector<int> age = this_year - birth_year;

//        const size_t segment_15_19 = age.count_between(15, 19);
//        const size_t segment_20_24 = age.count_between(20, 24);
//        const size_t segment_25_29 = age.count_between(25, 29);
//        const size_t segment_30_34 = age.count_between(30, 34);
//        const size_t segment_35_39 = age.count_between(35, 39);
//        const size_t segment_40 = age.count_between(40, 85);

//        const size_t segment_total = segment_15_19+segment_20_24+segment_25_29+segment_30_34+segment_35_39+segment_40;

//        std::cout << "segment_15_19: " << segment_15_19 << "(" << 100.0*(double)segment_15_19/(double)segment_total << ")%" << std::endl;
//        std::cout << "segment_20_24: " << segment_20_24 << "(" << 100.0*(double)segment_20_24/(double)segment_total << ")%" << std::endl;
//        std::cout << "segment_25_29: " << segment_25_29 << "(" << 100.0*(double)segment_25_29/(double)segment_total << ")%" << std::endl;
//        std::cout << "segment_30_34: " << segment_30_34 << "(" << 100.0*(double)segment_30_34/(double)segment_total << ")%" << std::endl;
//        std::cout << "segment_35_39: " << segment_35_39 << "(" << 100.0*(double)segment_35_39/(double)segment_total << ")%" << std::endl;
//        std::cout << "segment_40: " << segment_40 << "(" << 100.0*(double)segment_40/(double)segment_total << ")%" << std::endl;

//        std::cout <<  std::endl
//                  << "Age mode: " << std::endl;

//        const Vector<size_t> missing_values_indices = age.arrange_equal_to_indices(2017+999999);

//        const size_t age_mode = age.calculate_mode_missing_values(missing_values_indices);

//        std::cout << "Mode: " << age_mode << std::endl;

//        size_t segment_18_24 = age.count_between(18, 24);
//        size_t segment_25_34 = age.count_between(25, 34);
//        size_t segment_35_44 = age.count_between(35, 44);
//        size_t segment_45_54 = age.count_between(45, 54);
//        size_t segment_56_64 = age.count_between(55, 64);
//        size_t segment_65 = age.count_between(65, 85);

//        std::cout << "segment_18_24: " << segment_18_24 << std::endl;
//        std::cout << "segment_25_34: " << segment_25_34 << std::endl;
//        std::cout << "segment_35_44: " << segment_35_44 << std::endl;
//        std::cout << "segment_45_54: " << segment_45_54 << std::endl;
//        std::cout << "segment_56_64: " << segment_56_64 << std::endl;
//        std::cout << "segment_65: " <<  segment_65 << std::endl;
}


void campaign_analysis(void)
{
        std::cout << "Campaign analysis: " << std::endl;

//        const Vector<std::string> campaign_names = redemption_data.arrange_column("campaignName").arrange_unique();
//        const Vector<size_t> campaign_redemptions = redemption_data.arrange_column("campaignName").count_unique();

//        std::cout << "Campaign names: " << campaign_names.to_column_matrix() << std::endl;
//        std::cout << "Campaign redemptions: " << campaign_redemptions.to_column_matrix() << std::endl;

//        missing_values_indices.to_time();

//        const Vector<int> delivery = redemption_data.arrange_column("deliveredAt").remove_element(0).string_to_int();
//        const Vector<int> redemption = redemption_data.arrange_column("redeemAt").remove_element(0).string_to_int();

//        Vector<int> difference_days(redemed_coupons);
//        Vector<int> difference_hours(redemed_coupons);

//        for(size_t i = 0; i < redemed_coupons; i++)
//        {
//            if(delivery[i] > redemption[i])
//            {
//                std::cout << i << std::endl;

//                char buff[70];

//                time_t time = delivery[i];

//                struct tm* my_time = gmtime(&time);

//                   if (strftime(buff, sizeof buff, "%A %c", my_time)) {
//                       puts(buff);
//                   } else {
//                       puts("strftime failed");
//                   }

//               time = redemption[i];

//               my_time = gmtime(&time);

//                  if (strftime(buff, sizeof buff, "%A %c", my_time)) {
//                      puts(buff);
//                  } else {
//                      puts("strftime failed");
//                  }
//                system("pause");
//            }

//            //difference[i] = difftime(redemption[i], delivery[i]);
//        }

//        for(size_t i = 0; i < redemed_coupons; i++)
//        {
//            difference_days[i] = difftime(redemption[i], delivery[i])/86400;
//            difference_hours[i] = difftime(redemption[i], delivery[i])/3600;
//        }

//        difference_hours = difference_hours.arrange_between(0,24);

//        std::cout << difference_hours.calculate_statistics() << std::endl;

//        std::cout << difference_hours.arrange_unique() << std::endl;

//        std::cout << std::endl;

//        std::cout << difference_hours.count_unique() << std::endl;

}


void test_time(void)
{
    struct tm  timeinfo;

    int year = 2017;
    int month = 11;
    int month_day = 6;

    int hours = 11;
    int minutes = 44;
    int seconds = 30;

    timeinfo.tm_year = year - 1900;
    timeinfo.tm_mon = month - 1;
    timeinfo.tm_mday = month_day;

    timeinfo.tm_hour = hours;
    timeinfo.tm_min = minutes;
    timeinfo.tm_sec = seconds;

    std::cout << timeinfo.tm_hour  << std::endl;

    time_t time = mktime(&timeinfo);

    struct tm* returned_timeinfo = gmtime(&time);

    std::cout << returned_timeinfo->tm_year + 1900 << std::endl;
    std::cout << returned_timeinfo->tm_mon + 1 << std::endl;
    std::cout << returned_timeinfo->tm_mday  << std::endl;

    std::cout << returned_timeinfo->tm_hour  << std::endl;
    std::cout << returned_timeinfo->tm_min  << std::endl;
    std::cout << returned_timeinfo->tm_sec  << std::endl;
}


void cluster_analysis(void)
{
    std::cout << "Cluster analysis: " << std::endl;

    Matrix<std::string> data;
    data.load_strings(clean_data_filename, ',');

    const Matrix<std::string> redemption_data = data.filter_column_not_equal_to("redeemAt", "NA");

    // Age

//    const Vector<double> birth_year = redemption_data.arrange_column("birth_year").remove_element(0).string_to_double().arrange_between(1932.0, 2002.0);

//    const Vector<double> age = birth_year*-1 + 2017;

//    std::cout << age.calculate_statistics() << std::endl;

//    const KMeansResults<double> k_means_results = age.to_column_matrix().calculate_k_means(3);

//    std::cout << k_means_results.means << std::endl;

//    for(size_t i = 0; i < k_means_results.clusters.size(); i++)
//    {
//        std::cout << k_means_results.clusters[i].calculate_mean() << std::endl;
//    }

    // Redeemed coupons

//    const Vector<double> client_redemptions = redemption_data.arrange_column("clientId").remove_element(0).count_unique().arrange_between(0,1000).to_double();

//    std::cout << "Number of clients: " << client_redemptions.size() << std::endl;

//    std::cout << client_redemptions.calculate_statistics() << std::endl;

//    const KMeansResults<double> k_means_results = client_redemptions.to_column_matrix().calculate_k_means(3);

//    std::cout << k_means_results.means << std::endl;

//    for(size_t i = 0; i < k_means_results.clusters.size(); i++)
//    {
//        std::cout << k_means_results.clusters[i].size() << std::endl;
//    }

    // Time response

    const Vector<double> delivered_at = redemption_data.arrange_column("deliveredAt").remove_element(0).string_to_double();
    const Vector<double> redeemed_at = redemption_data.arrange_column("redeemAt").remove_element(0).string_to_double();

    const Vector<double> time_response = (redeemed_at - delivered_at).arrange_between(0.0,86400.0)/60.0;

    std::cout << time_response.size() << std::endl;
    std::cout << time_response.calculate_statistics() << std::endl;

    const KMeansResults<double> k_means_results = time_response.to_column_matrix().calculate_k_means(3);

    std::cout << k_means_results.means << std::endl;

    for(size_t i = 0; i < k_means_results.clusters.size(); i++)
    {
        std::cout << k_means_results.clusters[i].size() << std::endl;
    }

}


int main(void)
{
    try
    {
        std::cout << "McDonald's Chile" << std::endl;

        srand((unsigned int)time(NULL));


//        data_preparation();

//        data_preparation_neural_designer();

//        integrity_analysis();

//        performance_analysis();

//        customer_analysis();

//        campaign_analysis();

        cluster_analysis();


        return(0);
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;

        return(1);
    }
}


// OpenNN: Open Neural Networks Library.
// Copyright (C) 2005-2017 Roberto Lopez.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
