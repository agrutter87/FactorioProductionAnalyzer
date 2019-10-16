local json = require "lib/json"

local inputs = {}
local outputs = {}

function acquireStats()
	-- Production Statistics
	for _, player in pairs(game.players) do
		for item, input_count in pairs(player.force.item_production_statistics.input_counts) do
			--player.print(item)
			--player.print(input_count)
			inputs[item] = input_count
		end
		
		for fluid, input_count in pairs(player.force.fluid_production_statistics.input_counts) do
			--player.print(fluid)
			--player.print(input_count)
			inputs[fluid] = input_count
		end
		--]]
		
		---[[ Count outputs
		for item, output_count in pairs(player.force.item_production_statistics.output_counts) do
			--player.print(item)
			--player.print(input_count)
			outputs[item] = output_count
		end
		
		for fluid, output_count in pairs(player.force.fluid_production_statistics.output_counts) do
			--player.print(fluid)
			--player.print(input_count)
			outputs[fluid] = output_count
		end
	end
end

function processStats()
	for thing, count in pairs(inputs) do
		--player.print(thing)
		--player.print(count)
	end

	for thing, count in pairs(outputs) do
		--player.print(thing)
		--player.print(count)
	end
end

function updateJSONFile()

	local inputdata = {}
	local outputdata = {}

	i = 1
	for name, value in pairs(inputs) do
		inputdata[i] = {["name"]=name, ["value"]=value}
		i = i + 1
	end
	
	i = 1
	for name, value in pairs(outputs) do
		outputdata[i] = {["name"]=name, ["value"]=value}
		i = i + 1
	end

	productiondata = {["inputs"]=inputdata, ["outputs"]=outputdata}
	
	outdata = {["productiondata"]=productiondata}
	
  --game.players[1].print(global.json)
	--local outjson = json:encode(outdata)
	
	local folder = "FactorioProductionAnalzyer/"
	local filename = "production_data.json"
	
	--game.write_file(folder..filename, outjson, false)
  game.write_file(folder..filename, json:encode(outdata), false)
end

script.on_event(defines.events.on_player_created, function(event)
    game.players[event.player_index].print{"recipe.hi"}
end)

script.on_event(defines.events.on_tick, function(event)
	if event.tick % 60 == 0 then

	acquireStats()
	processStats()
	updateJSONFile()

 	end
end)
