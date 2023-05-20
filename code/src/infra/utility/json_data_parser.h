/**
 * @file json_data_parser.h.
 * @date 9.08.2022
 * @author Yazilimperver
 * @brief JSON formatinda veri tiplerini ayiklama ve olusturmak icin kullanilabilece jenerik siniftir. Burada cereal kutuphanesi kullanildigindan, ilgili `serilestirici` siniflar hazirlanmalidir.
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef JSONDATAPARSER
#define JSONDATAPARSER
/**
 * @file json_data_parser.h.
 * @date 30.04.2022
 * @author Yazilimperver
 * @brief Gecirilen veri tiplerini Json formatinda okuyup/yazmak icin kullanilabilecek olan yardimci siniftir.
 * 		  Bu sinif sayesinde, dosya islemleri kotarilmaktadir. 
 * 		  Alt tarafta Cereal kutuphanesi kullanilmaktadir (Json icin de, Cereal RapidJSON kullanmakta)
 * 		  Ilgili veri tipleinin bu sinif ile kulanilabilmesi icin, gerekli cereal `serializer/deserializer`  siniflari yazilmis olmalidir
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#include "cereal/archives/json.hpp"
#include <fstream>
#include <optional>

template <class T>
class JsonDataParser {
public:
	std::optional<T> Deserialize(std::string_view fileName) {
		std::ifstream is(fileName.data());

		if (is.is_open()) {
			try {
				T parsedData;
				cereal::JSONInputArchive archive_in(is);
				archive_in(parsedData);

				return parsedData;
			}
			catch (cereal::RapidJSONException&) {
				return std::nullopt;
			}
			catch (cereal::Exception& e) {
				std::cout << "Exception! " << e.what();
				return std::nullopt;
			}
		}
		else {
			return std::nullopt;
		}
	}

	bool Serialize(std::string_view fileName, const T& data, std::string_view jsonObjName = "Object") {
		try {
			std::ofstream os(fileName.data());

			cereal::JSONOutputArchive archive_out(os);
			archive_out(cereal::make_nvp(jsonObjName.data(), data));

			return true;
		}
		catch (cereal::RapidJSONException&) {
			return false;
		}
	}
};

#endif // !JSONDATAPARSER

/**
Copyright (c) [2022][Yazilimperver - yazilimpervergs@gmail.com]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */