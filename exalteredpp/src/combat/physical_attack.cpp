#include "combat/physical_attack.h"

#include "dice_roller/dice_roller_options.h"

namespace combat {

  attack_declaration attack_declaration::declare()
  {
    return attack_declaration();
  }

  attack_declaration attack_declaration::declare_as(std::initializer_list<attack_attribute> attributes)
  {
    attack_declaration res;
    res._atk->attack_attributes = attributes;
    return res;
  }

  attack_declaration& attack_declaration::is(std::initializer_list<attack_attribute> attributes)
  {
    _atk->attack_attributes = attributes;
    return *this;
  }

  attack_declaration& attack_declaration::is(attack_attribute attribute)
  {
    if (!commons::contains(_atk->attack_attributes, attribute))
      _atk->attack_attributes.push_back(attribute);
    return *this;
  }

  attack_declaration& attack_declaration::is_not(attack_attribute attribute)
  {
    if (commons::contains(_atk->attack_attributes, attribute))
      _atk->attack_attributes.erase(std::find(_atk->attack_attributes.begin(), _atk->attack_attributes.end(), attribute));
    return *this;
  }

  attack_declaration& attack_declaration::with(const equip::weapon& w)
  {
    _atk->weapon = w;
    return *this;
  }

  attack_declaration& attack_declaration::with_action_penalty(unsigned int vd_penalty)
  {
    _atk->action_penalty = vd_penalty;
    return *this;
  }

  attack_declaration& attack_declaration::attacker(std::shared_ptr<character::character> attacker)
  {
    _atk->attacker = attacker;
    return *this;
  }

  defense_declaration attack_declaration::declared() const
  {
    return defense_declaration (_atk);
  }

  std::vector<target_vd> defense_declaration::possible_vds() const
  {
    bool can_dodge = !(commons::contains(_atk->attack_attributes, attack_attribute::NON_DODGEABLE)),
        can_parry = !(commons::contains(_atk->attack_attributes, attack_attribute::NON_PARRYABLE));

    std::vector<target_vd> result;
    if (can_dodge) result.push_back(target_vd::PHYSICAL_DODGE);
    if (can_parry) result.push_back(target_vd::PHYSICAL_PARRY);

    return result;
  }

  precision_roll defense_declaration::dodge(std::shared_ptr<character::character> c, const calculator::derived_value_calculator& calculator) const
  {
    _atk->defender = c;
    _atk->vd = target_vd::PHYSICAL_DODGE;
    auto vd = calculator.compute_physical_vd(*c, ability::ability_enum::MELEE);
    _atk->vd_value = vd.dodge_vd;
    _atk->vd_balance = vd.dodge_balance;

    return precision_roll(_atk);
  }

  precision_roll defense_declaration::parry_with(std::shared_ptr<character::character> c, const calculator::derived_value_calculator& calculator, ability::ability_enum parry_ability) const
  {
    _atk->defender = c;
    _atk->vd = target_vd::PHYSICAL_PARRY;
    auto vd = calculator.compute_physical_vd(*c, parry_ability);
    _atk->vd_value = vd.parry_vd;
    _atk->vd_balance = vd.parry_balance;

    return precision_roll(_atk);
  }

  precision_roll defense_declaration::defend_with_value(target_vd vd, unsigned int vd_value, unsigned int vd_balance)
  {
    _atk->vd = vd;
    _atk->vd_value = vd_value;
    _atk->vd_balance = vd_balance;

    return precision_roll(_atk);
  }


  precision_roll& precision_roll::precision(unsigned int precision_dice)
  {
    _atk->precision_dice = precision_dice;
    return *this;
  }

  precision_roll& precision_roll::precision(attribute::attribute_enum attribute, const ability::ability_name& ability)
  {
    if (_atk->attacker)
      _atk->precision_dice = _atk->attacker->attribute(attribute) + _atk->attacker->get(ability) + _atk->weapon.precision_bonus();

    return *this;
  }

  precision_roll& precision_roll::precision(attribute::attribute_enum attribute, const ability::ability_name& ability, const std::string& specialisation)
  {
    if (_atk->attacker)
      _atk->precision_dice = _atk->attacker->attribute(attribute) + _atk->attacker->get(ability)[specialisation] + _atk->weapon.precision_bonus();

    return *this;
  }

  precision_roll& precision_roll::bonus(unsigned int bonus_successes)
  {
    _atk->precision_external_bonus = bonus_successes;
    return *this;
  }

  precision_roll& precision_roll::malus(unsigned int malus_successes)
  {
    _atk->precision_external_malus = malus_successes;
    return *this;
  }

  precision_roll& precision_roll::internal_bonus(unsigned int internal_bonus_dice)
  {
    _atk->precision_internal_bonus = internal_bonus_dice;
    return *this;
  }

  precision_roll& precision_roll::internal_malus(unsigned int internal_malus_dice)
  {
    _atk->precision_internal_malus = internal_malus_dice;
    return *this;
  }

  precision_roll& precision_roll::target(body_target target)
  {
    _atk->target = target;
    _atk->body_part_rolled = true;
    return *this;
  }

  precision_roll& precision_roll::do_not_target()
  {
    _atk->target = body_target::NO_TARGET;
    _atk->body_part_rolled = false;
    return *this;
  }

  unsigned int precision_roll::pool() const
  {
    return _atk->precision_dice + _atk->precision_internal_bonus - _atk->precision_internal_malus;
  }

  int precision_roll::external_bonus() const
  {
    return _atk->precision_external_bonus - _atk->precision_external_malus;
  }

  vd_application precision_roll::apply(std::shared_ptr<dice::abstract_dice_roller> dice_roller)
  {
    if (!_atk->precision_rolled)
      {
        if (_atk->precision_dice == 0 && _atk->attacker)
          {
            // compute precision based on attacker and weapon stats.
            unsigned int attribute_prec = _atk->attacker->attribute(_atk->weapon.precision_attribute());

            unsigned int best_ability = 0;
            for (auto ability: _atk->weapon.relevant_abilities())
              {
                if (_atk->attacker->get(ability) > best_ability)
                  best_ability = _atk->attacker->get(ability);
              }
            _atk->precision_dice = attribute_prec + best_ability + _atk->weapon.precision_bonus();
          }

        auto precisionpool = dice::pool(pool());
        dice_roller->with_pool(precisionpool);
        unsigned int roll_result = dice_roller->throw_dice() + _atk->precision_external_bonus - _atk->precision_external_malus;
        _atk->precision_rolled = true;
        _atk->precision_roll_result = dice::roll_result(roll_result);
      }

    return vd_application(_atk);
  }

  vd_application precision_roll::with_successes(unsigned int successes)
  {
    _atk->precision_rolled = true;
    _atk->precision_roll_result = successes;
    return vd_application(_atk);
  }

  bool vd_application::hits() const
  {
    return _atk->precision_roll_result > _atk->vd_value;
  }

  outcome vd_application::on_fail() const
  {
    outcome failure;

    failure._hit = false;
    failure._can_counter = (_atk->vd == target_vd::PHYSICAL_PARRY);
    failure._final_damage = 0;
    failure._action_penalty = _atk->action_penalty;

    return failure;
  }

  raw_damage_and_position_computation vd_application::on_success() const
  {
    _atk->raw_damage_dice = _atk->precision_roll_result - _atk->vd_value;

    return raw_damage_and_position_computation(_atk);
  }

  vd_application& vd_application::bonus(unsigned int bonus_successes)
  {
    _atk->vd_value += bonus_successes;
    return *this;
  }

  vd_application& vd_application::malus(unsigned int malus_successes)
  {
    _atk->vd_value -= malus_successes;
    return *this;
  }

  raw_damage_and_position_computation& raw_damage_and_position_computation::base_damage(unsigned int basedamage)
  {
    if (!_atk->attacker)
      {
        _atk->weapon.with_base_damage(basedamage);
      }
    return *this;
  }

  raw_damage_and_position_computation& raw_damage_and_position_computation::min_damage(unsigned int basedamage)
  {
    if (!_atk->attacker)
      {
        _atk->weapon.with_min_damage(basedamage);
      }
    return *this;
  }

  raw_damage_and_position_computation& raw_damage_and_position_computation::damage_type(damage_type_enum damage_type)
  {
    if (!_atk->attacker)
      {
        _atk->weapon.with_damage_type(damage_type);
      }
    return *this;
  }

  raw_damage_and_position_computation& raw_damage_and_position_computation::attribute(unsigned int attribute_value)
  {
    if (!_atk->attacker)
      {
        _atk->damage_attribute = attribute_value;
      }
    return *this;
  }

  raw_damage_and_position_computation& raw_damage_and_position_computation::drill(unsigned int weapon_drill)
  {
    if (!_atk->attacker)
      {
        _atk->weapon.with_drill(weapon_drill);
      }
    return *this;
  }

  body_target raw_damage_and_position_computation::target() const
  {
    if (!_atk->body_part_rolled)
      {
        body_part_roller roller;
        _atk->target = roller.roll_body_part();
        _atk->body_part_rolled = true;
      }
    return _atk->target;
  }

  void raw_damage_and_position_computation::compute_post_soak_pool(unsigned int soak, unsigned int armored_soak) const
  {
    unsigned int raw_damage = _atk->raw_damage();
    unsigned int final_soak = soak + dice::pool(armored_soak - _atk->weapon.drill());
    unsigned int raw = dice::pool(raw_damage - final_soak), min = _atk->weapon.minimum_damage();

    _atk->post_soak_damage = std::max(raw, min);
    _atk->is_damage_from_minimum = raw < min;
  }

  void raw_damage_and_position_computation::compute_post_soak_pool(const calculator::derived_value_calculator& calculator) const
  {

    unsigned int raw_damage = _atk->raw_damage();

    auto soak = calculator.compute_physical_vd(*_atk->defender, ability::ability_enum::MELEE);
    unsigned int soak_value = 0;

    // refactor this switch inside the physical vd
    switch(_atk->weapon.damage_type())
      {
      case damage_type_enum::BASHING:
        soak_value = soak.bashing_soak;
        break;
      case damage_type_enum::LETHAL:
        soak_value = soak.lethal_soak;
        break;
      case damage_type_enum::AGGRAVATED:
        soak_value = soak.aggravated_soak;
        break;
      }

    // TODO when armor and equipment are added. Right now armored soak is 0.
    unsigned int final_soak = soak_value + dice::pool(0 - _atk->weapon.drill());
    unsigned int raw = (raw_damage - final_soak), min = _atk->weapon.minimum_damage();

    auto pool = raw > min ? dice::pool(raw) : dice::pool(min);
    _atk->post_soak_damage = pool;
    _atk->is_damage_from_minimum = raw < min;
  }

  bool raw_damage_and_position_computation::passes(unsigned int soak, unsigned int armored_soak) const
  {
    compute_post_soak_pool(soak, armored_soak);
    return _atk->post_soak_damage > 0;
  }

  bool raw_damage_and_position_computation::passes(const calculator::derived_value_calculator& calculator) const
  {
    compute_post_soak_pool(calculator);
    return _atk->post_soak_damage > 0;
  }

  outcome raw_damage_and_position_computation::on_fail() const
  {
    outcome failure;

    failure._hit = true;
    failure._final_damage = 0;
    failure._action_penalty = _atk->action_penalty;

    return failure;
  }

  post_soak_damage raw_damage_and_position_computation::on_pass(unsigned int soak, unsigned int armored_soak) const
  {
    compute_post_soak_pool(soak, armored_soak);
    return post_soak_damage(_atk);
  }

  post_soak_damage raw_damage_and_position_computation::on_pass(const calculator::derived_value_calculator& calculator) const
  {
    compute_post_soak_pool(calculator);
    return post_soak_damage(_atk);
  }

  bool post_soak_damage::passes (unsigned int hardness) const
  {
    return (_atk->post_soak_damage > hardness) || _atk->is_damage_from_minimum;
  }

  bool post_soak_damage::passes(const calculator::derived_value_calculator&) const
  {
    // auto vds = calculator.compute_physical_vd(*_atk->defender, ability::ability_enum::MELEE);
    // there is no hardness yet in physical vds so we're skipping this as well
    return true;
  }

  outcome post_soak_damage::on_fail() const
  {
    outcome failure;

    failure._hit = true;
    failure._final_damage = 0;
    failure._action_penalty = _atk->action_penalty;

    return failure;
  }

  post_hardness_damage post_soak_damage::on_pass() const
  {
    return post_hardness_damage(_atk);
  }

  final_damage post_hardness_damage::roll(std::shared_ptr<dice::abstract_dice_roller> dice_roller)
  {
    dice_roller->with_pool(_atk->post_soak_damage);
    _atk->damage_rolled = true;
    _atk->final_damage_result = dice_roller->throw_dice();
    return final_damage(_atk);
  }

  unsigned int final_damage::damage() const
  {
    return _atk->final_damage_result;
  }

  final_damage& final_damage::knockback_meters(unsigned int successes)
  {
    if (_atk->tried_to_push)
      return *this;

    _atk->tried_to_push = true;
    _atk->final_damage_result -= successes;
    if (successes > _atk->vd_balance)
      {
        _atk->meters_pushed = successes - _atk->vd_balance;
        _atk->was_knocked_back = true;
      }
    return *this;
  }

  final_damage& final_damage::knockdown(unsigned int successes)
  {
    if (_atk->tried_to_push)
      return *this;

    _atk->tried_to_push = true;
    _atk->final_damage_result -= successes;
    if (successes > _atk->vd_balance)
      _atk->was_knocked_down = true;
    return *this;
  }

  outcome final_damage::end_attack() const
  {
    outcome final_result;

    final_result._hit = true;
    final_result._can_counter = false;
    final_result._final_damage = _atk->final_damage_result;
    final_result._action_penalty = _atk->action_penalty;
    final_result._pushed = _atk->was_knocked_back;
    final_result._meters_pushed = _atk->meters_pushed;
    final_result._knocked = _atk->was_knocked_down;
    final_result._target = _atk->target;

    return final_result;
  }

  bool outcome::counter_available() const
  {
    return _can_counter;
  }

  unsigned int outcome::final_damage() const
  {
    return _final_damage;
  }

  unsigned int outcome::vd_penalty_on_attacker() const
  {
    return _action_penalty;
  }

  unsigned int outcome::meters_pushed() const
  {
    return _meters_pushed;
  }

  body_target  outcome::target_hit() const
  {
    return _target;
  }

  bool outcome::was_hit() const
  {
    return _hit;
  }

  bool outcome::was_pushed() const
  {
    return _pushed;
  }

  bool outcome::was_knocked_down() const
  {
    return _knocked;
  }


}
