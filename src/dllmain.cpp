/*
 *  MUA/XML2 Limit Adjuster - Base Code
 *      Original work Copyright (C) 2013-2014 ThirteenAG <thirteenag@gmail.com>
 *      Original work Copyright (C) 2014 LINK/2012 <dma_2012@hotmail.com>
 *      Modified work Copyright (C) 2018 nikita488
 *      Licensed under the MIT License (http://opensource.org/licenses/MIT)
 */
#include <windows.h>
#include <LimitAdjuster.h>
#include <ini_parser/ini_parser.hpp>
#include <injector/utility.hpp>
#include <injector/gvm/translator.hpp>

// Stores an handler for a specific limit
struct LimitHandler
{ 
    int         id;         // Id for the key
    Adjuster*   adjuster;   // Adjuster to handle the key
};

int AdjustLimits();
void AdjustLimits(const std::map<std::string, std::string>&);

// Map of name of limit and adjuster to handle that limit
static std::map<std::string, LimitHandler> limits;


// Entry point
extern "C"
BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    if(reason == DLL_PROCESS_ATTACH)
    {
        auto& gvm = injector::address_manager::singleton();
        
        if(gvm.IsUnknown()) // Game could not be detected?
            gvm.RaiseCouldNotDetect();  // Ops...
        else
        {
            AdjustLimits();             // Run the limit adjuster
        }
    }
    return TRUE;
}




/*
 * -------- Basic Limit Adjuster Running --------
 */

/*
 *  Reads all key-value pairs from the 'ini' section 'secname' and add them to the 'output' pair
 *  If pair already exists on the output pair it's overriden
 */
void ReadSection(const linb::ini& ini, const char* secname, std::map<std::string, std::string>& output)
{
    if(secname)
    {
        for(auto sec = ini.begin(); sec != ini.end(); ++sec)
        {
            // Find section named secname
            if(!strcmp(sec->first.c_str(), secname))
            {
                // Push all kv pairs to the output map
                auto& section = sec->second;
                for(auto it = section.begin(); it != section.end(); ++it)
                    output[it->first] = it->second;
                break;
            }
        }
    }
}

/*
 *  Adjust the limits asked by the ini file
 */
int AdjustLimits()
{
    std::map<std::string, std::string> keys;
    linb::ini ini("MUA.XML2.LimitAdjuster.ini");           // Open the ini
    const char* secname = 0;

    // Find which section we should read on the ini
    if(Adjuster::IsMUA()) secname = "MUALIMITS";
    else if(Adjuster::IsXML2()) secname = "XML2LIMITS";

    // Configurable options such as debug text key
    /*auto& options = ini["OPTIONS"];
    for(auto it = options.begin(); it != options.end(); ++it)
    {
        auto& pair = *it;
        try {
            
            if(!pair.first.compare("DebugTextKey"))
                vkDebugText = std::stoi(pair.second, nullptr, 0);

        } catch(const std::logic_error& ex) {
            char buf[512];
            sprintf(buf, "Invalid value on option %s\n%s\n", pair.first.c_str(), ex.what());
            MessageBoxA(0, buf, "Limit Adjuster", MB_ICONERROR);
        }
    }*/

    // Parse section in search of limits
    if(secname)
    {
        ReadSection(ini, "LIMITS", keys);
        ReadSection(ini, secname, keys);
        AdjustLimits(keys);
    }

    return 0;
}


/*
 *  Finds all the limit handlers
 */
void FindHandlers(std::map<std::string, LimitHandler>& handlers)
{
    LimitHandler k;
    auto& adjusters = Adjuster::GetAdjusters();
    
    // Find all adjusters present on this build and build the map of handlers
    for(auto it = adjusters.begin(); it != adjusters.end(); ++it)
    {
        Adjuster* adjuster = *it;
        if(auto* limits = adjuster->GetLimits())        // Get limits this adjuster can handle
        {
            // For each limit this adjuster can handle...
            for(auto* limit = limits; limit->name; ++limit)
            {
                // ...add it to the handlers map
                k.adjuster  = adjuster;
                k.id        = limit->id;
                handlers[limit->name] = k;
            }
        }
    }
}

/*
 *  Reads an section of limits to be changed
 */
void AdjustLimits(const std::map<std::string, std::string>& section)
{
    // Find the handler for each limit
    FindHandlers(::limits);
    
    // Parse the section and call the handler for each limit
    for(auto it = section.begin(); it != section.end(); ++it)
    {
        auto pair = limits.find(it->first);   // Find this limit handler
        if(pair != limits.end())
        {
            try
            {
                // Change the limit
                LimitHandler& handler = pair->second;
                handler.adjuster->ChangeLimit(handler.id, it->second);
            }
            catch(const std::exception& ex)
            {
                // ...ops... something wrong happened at ChangeLimit, failed to convert from string to int?
                // Dunno, let's report it to the user
                char buf[512];
                sprintf(buf, "Failed to change limit for '%s' with value '%s'.\nReason: %s\n",
                                it->first.c_str(), it->second.c_str(), ex.what());
                MessageBoxA(0, buf, "Limit Adjuster", MB_ICONERROR);
            }
        }
    }

    // Run Process()
    std::map<Adjuster*, int> adjz;   // list of already processed adjusters (int is dummy, too lazy to use std::set)
    for(auto it = limits.begin(); it != limits.end(); ++it)
    {
        auto* adj = it->second.adjuster;
        if(adjz[adj]++ == 0) adj->Process();    // Run only once for each Adjuster*
    }
}





void* injector::address_manager::translator(void* p)
{
    // The following must be at the top
    auto& t = address_translator_manager::singleton();

    // Then we need a fallback that will return the original address if no address was found for it
    struct fallbacker : injector::address_translator
    {
        virtual void* fallback(void* p) const
        {
            return p;
        }
    };
    static fallbacker fb;

    return t.translator(p);
}