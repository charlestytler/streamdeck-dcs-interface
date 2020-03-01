// Copyright 2020 Charles Tytler

#include "pch.h"

#include "DcsInterface.h"

#include <iostream> //TODO: delete after testing

DcsInterface::DcsInterface(const int rx_port, const int tx_port)
    : dcs_socket_(rx_port, tx_port)
{
}

void DcsInterface::register_dcs_monitor(const int dcs_id, const std::string &context)
{
    if (dcs_monitor_map_.find(dcs_id) == dcs_monitor_map_.end())
    {
        dcs_monitor_map_[dcs_id] = std::vector<std::string>();
    }
    dcs_monitor_map_[dcs_id].push_back(context);
}

void DcsInterface::process_next_dcs_events()
{
    std::queue<std::string> tokens = {};
    dcs_socket_.DcsReceive(":", "*", tokens);
    while (!tokens.empty())
    {
        std::string dcs_event = tokens.front();
        tokens.pop();

        // Parse dcs_event string of the form:
        //   "<dcs_id>=<reported_value>"
        const std::string delim = "=";
        const auto delim_loc = dcs_event.find(delim);
        const int dcs_id = std::stoi(dcs_event.substr(0, delim_loc));
        const std::string reported_value = dcs_event.substr(delim_loc + delim.size(), dcs_event.size());

        if (dcs_monitor_map_.find(dcs_id) != dcs_monitor_map_.end())
        {
            handle_dcs_event(dcs_id, reported_value);
        }
    }
}

void DcsInterface::handle_dcs_event(const int dcs_id, const std::string value)
{
    // Placeholder for initial testing.
    std::cout << "DCS ID: " << dcs_id << std::endl;
    std::cout << "Value: " << value << std::endl;
}