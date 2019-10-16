require("json")

local inputdata = {}
local outputdata = {}

function acquireStats()
	-- Production Statistics
	for _, player in pairs(game.players) do
		i = 1
		for name, value in pairs(player.force.item_production_statistics.input_counts) do
			--player.print(item)
			--player.print(input_count)
			--inputs[name] = value
			inputdata[i] = {["name"]=name, ["value"]=value}
			i = i + 1
		end
		
		for name, value in pairs(player.force.fluid_production_statistics.input_counts) do
			--player.print(fluid)
			--player.print(input_count)
			--inputs[fluid] = input_count
			inputdata[i] = {["name"]=name, ["value"]=value}
			i = i + 1
		end
		
		i = 1
		for name, value in pairs(player.force.item_production_statistics.output_counts) do
			--player.print(item)
			--player.print(input_count)
			--outputs[item] = output_count
			outputdata[i] = {["name"]=name, ["value"]=value}
			i = i + 1
		end
		
		for fluid, output_count in pairs(player.force.fluid_production_statistics.output_counts) do
			--player.print(fluid)
			--player.print(input_count)
			--outputs[fluid] = output_count
			outputdata[i] = {["name"]=name, ["value"]=value}
			i = i + 1
		end
	end
end

function updateJSONFile(timestamp)

	productiondata = {["timestamp"]=timestamp, ["inputs"]=inputdata, ["outputs"]=outputdata}
	
	outdata = {["productiondata"]=productiondata}
	
	local outjson = global.json.stringify(outdata)
	
	local folder = "FactorioProductionAnalyzer/"
	local filename = "production_data.json"
	
	game.write_file(folder..filename, outjson, false)
end

script.on_event(defines.events.on_player_created, function(event)
    game.players[event.player_index].print{"recipe.hi"}
end)

script.on_event(defines.events.on_tick, function(event)
	if event.tick % 60 == 0 then

	acquireStats()
	updateJSONFile(event.tick)

 	end
end)
