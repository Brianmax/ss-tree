local ReplicatedStorage =  game:GetService("ReplicatedStorage")
local Players = game:GetService("Players")

local displayValues = ReplicatedStorage:WaitForChild("GlobalVariables")
local status = displayValues:WaitForChild("Win")

local meta = script.Parent

meta.Touched:Connect(function(hit)
	local player = Players:GetPlayerFromCharacter(hit.Parent)
	if player then
		status.Value = true
		meta.Destroy()
	end
end)
