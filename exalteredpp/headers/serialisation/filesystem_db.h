#pragma once

#include "db_abstraction.h"
#include <QMap>

namespace serialisation {

  class filesystem_db : public db_abstraction
  {
  public:
    filesystem_db();

    // db_abstraction interface
    std::shared_ptr<character::character> load_character(const std::string& character_id) override;
    bool has_characters() const override;
    std::vector<std::string> character_list() override;
    void save_character(const std::shared_ptr<character::character> character) override;
    void remove_character(const std::string& character_id) override;
    void remove_character(unsigned int character_id) override;
    std::string character_name(const std::string& character_id) const override;
    std::shared_ptr<character::character> create_character( const std::string& name,
                                                const character::creation::character_type type,
                                                const character::exalt::caste caste,
                                                const character::attributes attributes,
                                                const character::abilities abilities,
                                                const character::virtues::virtues virtues,
                                                const character::power::power_container power_container) override;

  private:
    const std::string FILE_EXT, AVAILABLE_CHARACTERS_FILE;
    std::map<std::string, std::string> id_to_name;

    void save_json_to_file(std::string json, const std::string& filename) const;
    void save_character_map();
  };
}
